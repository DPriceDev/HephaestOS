// Copyright (C) 2022 David Price - All Rights Reserved
// This file is part of HephaistOS.
//
// HephaistOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaistOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAISTOS_FORMAT_FORMAT_H
#define HEPHAISTOS_FORMAT_FORMAT_H

#include "iterator.h"
#include "result.h"
#include "string_view.h"
#include "algorithms.h"
#include "charconv.h"

#include "format/formatter/formatter.h"
#include "format/format_arguments.h"
#include "format/format_state.h"
#include "format/parse_state.h"
#include "format/formatter/char_formatter.h"

namespace std {

    struct ArgumentIndex {
        size_t index;
        const char* nextCharacter;
    };

    /**
     * todo
     * @tparam OutputIterator
     * @param parseState
     * @param iterator
     * @param end
     * @return
     */
    template<std::outputIterator<const char &> OutputIterator>
    std::Result<ArgumentIndex> getArgumentIndex(
            ParseState& parseState, // todo: Switch to template param
            const char* iterator, // todo: Extract to character type template param
            const char* end // todo: Extract to character type template param
    ) {
        auto position = std::findIf(iterator, end, [] (auto character) {
            return character == ':' || character == '}';
        });

        // Invalid if a formatting : or end of argument } is not found
        if (position == end) {
            return std::Result<ArgumentIndex>::failure();
        }

        size_t index;
        if (position == iterator) {
            auto result = parseState.nextArgumentIndex();
            if (result.isNotValid()) {
                return std::Result<ArgumentIndex>::failure();
            }
            index = result.get();
        } else {
            auto result = std::fromChars<size_t>(iterator, position);
            if (!result.isValid()) {
                return std::Result<ArgumentIndex>::failure();
            }
            index = result.get();

            if (!parseState.checkArgumentIndex(index).isValid()) {
                return std::Result<ArgumentIndex>::failure();
            }
        }

        return std::Result<ArgumentIndex>::success(ArgumentIndex { index, position });
    }

    /**
     *
     * @param parseState
     * @param argumentIndex
     * @return
     */
    std::Result<bool> shouldParse(ParseState& parseState, const ArgumentIndex& argumentIndex) {
        switch (*argumentIndex.nextCharacter) {
            case '}':
                parseState.advanceTo(argumentIndex.nextCharacter);
                break;

            case ':':
                parseState.advanceTo(argumentIndex.nextCharacter + 1);
                break;

            default:
                // fails if format string is invalid (does not have : or })
                return std::Result<bool>::failure();
        }

        return std::Result<bool>::success(*argumentIndex.nextCharacter == ':');
    }

    template<std::outputIterator<const char &> OutputIterator>
    std::Result<OutputIterator> formatArgument(
            ParseState& parseState, // todo: Switch to template param
            FormatState& formatState, // todo: Switch to template param
            const BasicFormatArgument<FormatState>&& argument,
            const bool shouldParse
    ) {
        return visitFormatArgument(
                [&parseState, &formatState, &shouldParse] (auto arg) {
                    if constexpr (std::same_as<decltype(arg), MonoState>) {
                        // Fail if argument is not present.
                        return std::Result<OutputIterator>::failure();
                    } else {
                        // Get the formatter for this type and format the argument.
                        Formatter<decltype(arg), char> formatter;

                        if (shouldParse) {
                            parseState.advanceTo(formatter.parse(parseState));
                        }

                        auto result = formatter.format(arg, formatState);
                        return Result<OutputIterator>::success(result);
                    }
                },
                argument
        );
    }

    /**
     *
     * @tparam OutputIterator
     * @param output
     * @param toFormat
     * @param format
     * @return
     */
    template<std::outputIterator<const char &> OutputIterator>
    std::Result<OutputIterator> handleFormat(
            const char* iterator, // todo: Extract to character type template param
            const char* end, // todo: Extract to character type template param
            ParseState& parseState, // todo: Switch to template param
            FormatState& formatState // todo: Switch to template param
    ) {
        auto result = getArgumentIndex<OutputIterator>(parseState, iterator, end);
        if (!result.isValid()) {
            return std::Result<OutputIterator>::failure();
        }
        auto argumentIndex = result.get();

        auto shouldParseResult = shouldParse(parseState, argumentIndex);
        if (!shouldParseResult.isValid()) {
            return std::Result<OutputIterator>::failure();
        }

        return formatArgument<OutputIterator>(
                parseState,
                formatState,
                formatState.argument(argumentIndex.index),
                shouldParseResult.get()
        );
    }

    // todo: Should this return the output iterator of the failed point?
    // todo: could I reduce this loop to nested stringviews?
    /**
     *
     * @tparam OutputIterator
     * @param output
     * @param format
     * @param args
     * @return
     */
    template<std::outputIterator<const char&> OutputIterator>
    std::Result<OutputIterator> dynamicFormatTo(
            OutputIterator output,
            std::StringView format,
            std::FormatArguments args
    ) {
        auto parsingState = ParseState(format, args.count());
        auto formatState = FormatState(args, output);

        const auto* iterator = parsingState.begin();
        const auto* end = parsingState.end();

        while (iterator != end) {
            // Start formatting argument if { is found
            if (*iterator == '{') {
                ++iterator;

                // Escape the { character and just print it
                if (*iterator == '{') {
                    *output++ = *iterator++;
                    continue;
                }

                // Update state to current output position and handle formatArgument
                formatState.advanceTo(output);
                auto result = handleFormat<OutputIterator>(iterator, end, parsingState, formatState);

                // Return failure if failed to format argument
                if (!result.isValid()) {
                    return result;
                }

                output = result.get();
                iterator = parsingState.begin();

                // Return failed if the format string did not have a closing } for the last argument
                if (*iterator != '}') {
                    return std::Result<OutputIterator>::failure();
                }

                ++iterator;
                continue;
            }

            // Print escaped } or fail if not escaped
            if (*iterator == '}') {
                ++iterator;

                if (*iterator != '}' || iterator == end) {
                    return std::Result<OutputIterator>::failure();
                }
            }

            // print the format string character to the output directly.
            *output++ = *iterator++;
        }

        return std::Result<OutputIterator>::success(output);
    }

    /**
     *
     * @tparam CharacterType
     * @tparam OutputIterator
     * @tparam Args
     * @param output
     * @param format
     * @param args
     * @return
     */
    template<std::convertableToStringView CharacterType, std::outputIterator<const char&> OutputIterator, class... Args>
    std::Result<OutputIterator> formatTo(
            OutputIterator output,
            CharacterType* format,
            Args&&...args
    ) {
        return dynamicFormatTo(
                output,
                std::StringView { format },
                std::makeFormatArguments(args...)
        );
    }

    // todo
    // template<class... Args>
    //size_t formatted_size(/*format-string*/<Args...> fmt, Args&&... args);
}

#endif //HEPHAISTOS_FORMAT_FORMAT_H

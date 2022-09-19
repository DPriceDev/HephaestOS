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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_FORMAT_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_FORMAT_H

#include "iterator.h"
#include "result.h"
#include "string_view.h"
#include "algorithm.h"
#include "charconv.h"

#include "format/formatter/formatter.h"
#include "format/format_arguments.h"
#include "format/format_state.h"
#include "format/parse_state.h"
#include "format/formatter/char_formatter.h"
#include "format/formatter/bool_formatter.h"
#include "format/formatter/int_formatter.h"
#include "format/formatter/floating_formatter.h"
#include "format/formatter/pointer_formatter.h"

namespace std {

    namespace detail {

        /**
         * Result Struct of getArgumentIndex, which contains the index
         * of the found argument, and the pointer to the next character
         * after the '{' of the format field.
         */
        struct ArgumentIndex {
            size_t index;
            const char* nextCharacter;
        };

        /**
         * This method will carry out formatting and outputting the provided
         * @param argument to the @tparam OutputIterator.
         *
         * This will getVisitorArray the @param argument; if the type is a std::Monostable, then
         * a failure result is returned as the argument is invalid.
         *
         * If the argument is a handle, then the format method on the handle is called
         * to format the custom type the handle contains. This returns the @tparam OutputIterator
         * in the @param formatState after formatting.
         *
         * If the argument is a standard argument, then the Formatter is constructed from the
         * argument type. If the @param shouldParse flag is true, then the formatter will first
         * parse the parse arguments from the @param parseState. The Formatter will format the
         * argument to the @tparam OutputIterator and the @tparam OutputIterator will be returned.
         *
         * The parse and format states are advanced in this method to the end of their parsed or
         * formatted ranges.
         */
        template<std::outputIterator<const char&> OutputIterator, class CharacterType>
        std::Result<OutputIterator> formatArgument(
            BasicParseState<CharacterType>& parseState, // todo: Switch to template param
            BasicFormatState<CharacterType, OutputIterator>& formatState, // todo: Switch to template param
            const BasicFormatArgument<BasicFormatState<CharacterType, OutputIterator>>&& argument,
            const bool shouldParse
        ) {
            return visitFormatArgument(
                [&parseState, &formatState, &shouldParse](auto arg) {
                    if constexpr (std::same_as<decltype(arg), MonoState>) {
                        // Fail if argument is not present.
                        return std::Result<OutputIterator>::failure();
                    } else if constexpr (std::same_as<decltype(arg), typename BasicFormatArgument<BasicFormatState<CharacterType, OutputIterator>>::handle>) {
                        // Call formatter from the handle for custom types
                        arg.format(parseState, formatState);
                        return Result<OutputIterator>::success(
                            formatState.out()
                        );
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
         * This method checks whether the formatter should also parse the parse arguments. This is
         * denoted by the existence of the ':' parse identifier.
         *
         * The @param parseState will be incremented to the next character after either a closing
         * format field '}', or one after the parse identifier ':' which should be the first parse
         * argument. If neither of these identifiers is present, then the result is failure.
         */
        template<class CharacterType>
        std::Result<bool> shouldParse(BasicParseState<CharacterType>& parseState, const char* nextCharacter) {
            switch (*nextCharacter) {
                case '}':
                    parseState.advanceTo(nextCharacter);
                    break;

                case ':':
                    parseState.advanceTo(nextCharacter + 1);
                    break;

                default:
                    // fails if format string is invalid (does not have : or })
                    return std::Result<bool>::failure();
            }

            return std::Result<bool>::success(*nextCharacter == ':');
        }

        /**
         * This method finds the Argument index and the next character in the format field.
         *
         * If the field contains and index, i.e. '{1}', then that index is used. Otherwise,
         * the next index from the @param parseState is used. If previous format fields
         * contained an index, and this one does not (or visa versa), then the field is
         * invalid and a failure result is returned.
         *
         * The next character is found from the position of the first parse identifier ':'
         * or closing format field identifier '}'. If neither are found, then a failure
         * result is returned.
         */
        template<std::outputIterator<const char&> OutputIterator, class CharacterType>
        std::Result<ArgumentIndex> getArgumentIndex(
            BasicParseState<CharacterType>& parseState,
            const char* iterator, // todo: Extract to character type template param
            const char* end // todo: Extract to character type template param
        ) {
            auto position = std::findIf(
                iterator, end, [](auto character) {
                    return character == ':' || character == '}';
                }
            );

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
         * This method handles formatting a format field. It will find the argument from either
         * the parse state, or the index in the format field, check if parsing is required, and then
         * format the argument to the output.
         * @return
         */
        template<std::outputIterator<const char&> OutputIterator, class CharacterType>
        std::Result<OutputIterator> handleFormatField(
            const char* iterator, // todo: Extract to character type template param
            const char* end, // todo: Extract to character type template param
            BasicParseState<CharacterType>& parseState,
            BasicFormatState<CharacterType, OutputIterator>& formatState
        ) {
            auto result = getArgumentIndex<OutputIterator>(parseState, iterator, end);
            if (!result.isValid()) {
                return std::Result<OutputIterator>::failure();
            }
            auto argumentIndex = result.get();

            auto shouldParseResult = shouldParse(parseState, argumentIndex.nextCharacter);
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
    }

    /**
     * DynamicFormatTo takes a @param format and a set of @param args and formats them together
     * and outputs them to the @param output iterator.
     *
     * This method is a non templated version of formatTo, and takes StringView and FormatArguments
     * classes instead of template parameters.
     *
     * The @param format consists of text, interlaced with '{}' format fields, which are
     * mark where the format arguments are to fall. These format fields can contain an index,
     * i.e. '{1}' and parse data, i.e. '{:b}', where ':' denotes the start of the parsing arguments.
     *
     * The call will fail (finish outputting early) if an error occurs. Errors can be:
     * - Mixing index '{1}' and non-index '{}'.
     * - Invalid parse arguments.
     * - Output iterator overflows the output memory.
     */
    template<class OutputIterator>
    std::Result<OutputIterator> dynamicFormatTo(
        OutputIterator output,
        std::StringView format,
        BasicFormatArguments<BasicFormatState<char, OutputIterator>> args
    ) {
        auto parsingState = BasicParseState<char>{ format, args.count() };
        auto formatState = BasicFormatState<char, OutputIterator> { args, output };

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
                auto result = detail::handleFormatField<OutputIterator>(iterator, end, parsingState, formatState);

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
     * FormatTo takes a @param format and a set of @param args and formats them together
     * and outputs them to the @param output iterator.
     *
     * This call converts the template parameters for format and args, to StringView and
     * FormatArguments, and calls the underlying dynamicFormatTo.
     *
     * The @param format consists of text, interlaced with '{}' format fields, which are
     * mark where the format arguments are to fall. These format fields can contain an index,
     * i.e. '{1}' and parse data, i.e. '{:b}', where ':' denotes the start of the parsing arguments.
     *
     * The call will fail (finish outputting early) if an error occurs. Errors can be:
     * - Mixing index '{1}' and non-index '{}'.
     * - Invalid parse arguments.
     * - Output iterator overflows the output memory.
     */
    template<std::convertableToStringView CharacterType, class OutputIterator, class... Args>
    std::Result<OutputIterator> formatTo(
        OutputIterator output,
        CharacterType* format,
        Args&& ... args
    ) {
        using State = BasicFormatState<char, OutputIterator>;
        return dynamicFormatTo(
            output,
            std::StringView { format },
            BasicFormatArguments<State> {
                makeFormatArguments<State>(args...)
            }
        );
    }
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_FORMAT_H

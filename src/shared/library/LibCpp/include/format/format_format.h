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

#include "format/formatter/formatter.h"
#include "format/format_arguments.h"
#include "format/format_state.h"
#include "format/parse_state.h"
#include "format/formatter/char_formatter.h"

namespace std {

    /**
     *
     * @tparam OutputIterator
     * @param output
     * @param toFormat
     * @param format
     * @return
     */
     // todo: Should this return the output iterator of the failed point?
    template<std::outputIterator<const char&> OutputIterator>
    std::Result<OutputIterator> dynamicFormatTo(
            OutputIterator output,
            std::StringView format,
            std::FormatArguments args
    ) {
        // parse string?

        auto parsingState = ParseState(format);
        auto formatState = FormatState(args, output);

        // todo: could I reduce this loop to nested stringviews?

        auto* begin = parsingState.begin();
        const auto* end = parsingState.end();
        while (begin != end) {

            if (*begin == '{') {
                ++begin;

                // if { is escaped, just print {
                if (*begin == '{') {
                    *output++ = *begin++;
                    continue;
                }

                // todo: Break into its own function

                // advance parse context to }
                // return parse context begin + 1

                formatState.advanceTo(output);

                // get position and parse format string

                // get argument for position
                auto argument = BasicFormatArgument<FormatState>('c');

                // todo: Return result if failure
                auto result = std::visitFormatArgument(
                        // todo: Break visitor
                        [&formatState] (auto arg) {
                            if constexpr (std::same_as<decltype(arg), std::MonoState>) {
                                return std::Result<OutputIterator>::failure();
                            } else {
                                std::Formatter<decltype(arg), char> formatter;
                                formatState.advanceTo(
                                        formatter.format(arg, formatState)
                                );
                                // todo: Need to return parse state here?
                                return std::Result<OutputIterator>::success(formatState.out());
                            }
                        },
                        argument
                );

                // todo: advance begin to where formatter left off - parse state?

                continue;
            }

            if (*begin == '}') {
                ++begin;

                if (*begin != '}') {
                    // todo: This is an error as it should be escaped, how to handle this? return result error?
                    return std::Result<OutputIterator>::failure();
                }
            }

            *output++ = *begin++;
        }

        return std::Result<OutputIterator>::success(output);
    }

    template<std::convertableToStringView CharacterType, std::outputIterator<const char&> OutputIterator, class... Args>
    std::Result<OutputIterator> formatTo(
            OutputIterator output,
            CharacterType* format,
            Args&&...args
    ) {
        return dynamicFormatTo(
                output,
                std::StringView { format }, // todo: Should this be a concept of a stringview?
                std::makeFormatArguments(args...)
        );
    }

    // todo
    // template<class... Args>
    //size_t formatted_size(/*format-string*/<Args...> fmt, Args&&... args);

}



#endif //HEPHAISTOS_FORMAT_FORMAT_H

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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_H

#include "iterator.h"
#include "result.h"
#include "string_view.h"

#include "format/formatter.h"
#include "format/format_arguments.h"
#include "format/format_state.h"

namespace std {
    /**
     *
     * @tparam OutputIterator
     * @param output
     * @param toFormat
     * @param format
     * @return
     */
    template<std::outputIterator<const char&> OutputIterator>
    std::Result<OutputIterator> formatTo(
            OutputIterator output,
            std::StringView format,
            std::FormatArguments args
    ) {
        // todo:
    }

    template<std::convertableToStringView CharacterType, std::outputIterator<const char&> OutputIterator, class... Args>
    std::Result<OutputIterator> formatTo(
            OutputIterator output,
            CharacterType* format,
            Args&&...args
    ) {
        return formatTo(
                output,
                std::StringView { format },
                std::makeFormatArguments(args...)
        );
    }

    // todo
    // template<class... Args>
    //size_t formatted_size(/*format-string*/<Args...> fmt, Args&&... args);

}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_H

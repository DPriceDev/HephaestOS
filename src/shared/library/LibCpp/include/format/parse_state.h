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

#ifndef HEPHAISTOS_PARSE_STATE_H
#define HEPHAISTOS_PARSE_STATE_H

#include "iterator.h"
#include "string_view.h"

namespace std {

    // todo
    template<class CharacterType>
    class BasicParseState {
        enum class CountingType { NOT_SET, MANUAL, AUTOMATIC };

        std::BaseStringView<CharacterType> format;
        std::size_t argumentCount;
        std::size_t argumentIndex { 0 };
        CountingType countingType { CountingType::NOT_SET };

    public:
        using characterType = CharacterType;
        using iterator = typename std::BaseStringView<CharacterType>::iterator;
        using constIterator = typename std::BaseStringView<CharacterType>::constIterator;

        explicit BasicParseState(
                std::BaseStringView<CharacterType> format,
                std::size_t argumentCount = 0
        ) : format(format), argumentCount(argumentCount) { }

        constexpr auto begin() const noexcept -> constIterator {
            return format.begin();
        }

        constexpr auto end() const noexcept -> constIterator {
            return format.end();
        }

        constexpr void advanceTo(constIterator location) {
            format = std::BaseStringView<CharacterType> { location };
        }

        constexpr auto nextArgumentIndex() -> std::Result<size_t> {
            if (countingType == CountingType::MANUAL || argumentIndex >= argumentCount) {
                return std::Result<size_t>::failure();
            }
            countingType = CountingType::AUTOMATIC;
            return std::Result<size_t>::success(argumentIndex++);
        }
        constexpr std::Result<size_t> checkArgumentIndex(size_t index) {
            if (index >= argumentCount || countingType == CountingType::AUTOMATIC) {
                return std::Result<size_t>::failure();
            }
            countingType = CountingType::MANUAL;
            return std::Result<size_t>::success(index);
        }
    };

    // todo
    // todo back insert?
    using ParseState = BasicParseState<char>;
}
#endif // HEPHAISTOS_PARSE_STATE_H
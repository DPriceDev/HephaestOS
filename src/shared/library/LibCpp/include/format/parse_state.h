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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_PARSE_STATE_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_PARSE_STATE_H

#include "iterator.h"
#include "string_view.h"

namespace std {

    /**
     * The parse state contains all of the state relating to parsing of the format
     * fields, e.g. '{1:b}', and the format string.
     *
     * This contains methods to check and get the indexes of the arguments. The
     * format string supports two exlusive types of indexing:
     * - Automatic: The parse state provides the index that is incremented for each
     *   argument.
     * - Manual: The index is extracted from the format field and checked is valid
     *   by the parse state.
     *
     * The parse state also contains the pointers to the beginning and end of the
     * format string, and advances the begin iterator to each format field as
     * required.
     */
    template<class Type>
    class BasicParseState {
        enum class CountingType { NOT_SET, MANUAL, AUTOMATIC };

        std::BaseStringView<Type> format_;
        std::size_t argumentCount_;
        std::size_t argumentIndex_ { 0 };
        CountingType countingType_ { CountingType::NOT_SET };

      public:
        using CharacterType = Type;
        using Iterator = typename std::BaseStringView<CharacterType>::Iterator;
        using ConstIterator = typename std::BaseStringView<CharacterType>::ConstIterator;

        // Constructor
        explicit BasicParseState(std::BaseStringView<CharacterType> format, std::size_t argumentCount = 0)
            : format_(format), argumentCount_(argumentCount) {}

        // Accessors
        constexpr auto begin() const noexcept -> ConstIterator { return format_.begin(); }

        constexpr auto end() const noexcept -> ConstIterator { return format_.end(); }

        constexpr void advanceTo(ConstIterator location) { format_ = std::BaseStringView<CharacterType> { location }; }

        // Operations

        /**
         * Gets the next argument index as the current argument count, and then increments
         * it. This allows the arguments to be fetched in order.
         *
         * This sets the counting type to automatic. If the counting type is already set to
         * manual, then a failure result is returned.
         */
        constexpr auto nextArgumentIndex() -> std::Result<std::size_t> {
            if (countingType_ == CountingType::MANUAL || argumentIndex_ >= argumentCount_) {
                return std::Result<std::size_t>::failure();
            }
            countingType_ = CountingType::AUTOMATIC;
            return std::Result<std::size_t>::success(argumentIndex_++);
        }

        /**
         * This checks that the index is a valid argument index, i.e. not greater than
         * the total argument count.
         *
         * This sets the counting type to manual. If the counting type is already set to
         * automatic, then a failure result is returned.
         */
        constexpr std::Result<std::size_t> checkArgumentIndex(size_t index) {
            if (index >= argumentCount_ || countingType_ == CountingType::AUTOMATIC) {
                return std::Result<std::size_t>::failure();
            }
            countingType_ = CountingType::MANUAL;
            return std::Result<std::size_t>::success(index);
        }
    };

    // Declaration of a char based parse state.
    using ParseState = BasicParseState<char>;
}// namespace std
#endif// HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_PARSE_STATE_H
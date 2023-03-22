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

#include "format_state.h"
#include "format_argument.h"
#include "array_base.h"

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_ARGUMENTS_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_ARGUMENTS_H

namespace std {

    namespace detail {
        /**
            * Temporary format arguments storage class used when constructing the
            * initial arguments.
            */
        template<class State, std::size_t Size>
        struct FormatArgumentStore {
            std::Array<BasicFormatArgument<State>, Size> array;

            // Constructor
            template<class... Args>
            explicit FormatArgumentStore(Args... arguments) : array(std::Array<BasicFormatArgument<State>, sizeof...(Args)> { arguments... }) { }

            auto size() const -> std::size_t {
                return Size;
            }

            auto data() const -> const BasicFormatArgument<State>* {
                return array.data();
            }
        };

        template<class State>
        struct FormatArgumentStore<State, 0> {
            explicit FormatArgumentStore() = default;

            auto size() const -> std::size_t {
                return 0;
            }

            auto data() const -> const BasicFormatArgument<State>* {
                return nullptr;
            }
        };
    }

    /**
     * Arguments class that stores the format arguments and allows access to get
     * each argument by index.
     */
    template<class State>
    class BasicFormatArguments {
        size_t size { };
        const BasicFormatArgument<State>* data;

    public:
        // Constructors
        BasicFormatArguments() noexcept = default;

        /**
         * Constructs the arguments for an argument store. This is an implicit construction
         * which allows the argument store to be converted directly to the arguments.
         */
        template<std::size_t Size>
        BasicFormatArguments(const detail::FormatArgumentStore<State, Size>& store) noexcept
            : size(store.size()),
              data(store.data()) { }

        // Accessors
        BasicFormatArgument<State> get(std::size_t index) const noexcept {
            // todo: if out of size, return monostate?
            return data[index];
        }

        auto count() -> std::size_t {
            return size;
        }
    };

    // Defines the format arguments for a char based state.
    using FormatArguments = BasicFormatArguments<std::FormatState>;

    /**
     * Constructs a temporary argument store that stores the provided @param args as a
     * set of BasicFormatArgument's.
     */
    template<class State, class... Args>
    detail::FormatArgumentStore<State, sizeof...(Args)> makeFormatArguments(Args&&... args) {
        return detail::FormatArgumentStore<State, sizeof...(Args)>(BasicFormatArgument<State>(args)...);
    }
}

#endif //HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_ARGUMENTS_H

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

#ifndef HEPHAISTOS_FORMAT_ARGUMENTS_H
#define HEPHAISTOS_FORMAT_ARGUMENTS_H

namespace std {

    // todo move or change
    template<class State, class... Args>
    struct FormatArgumentStore {
        // todo: Move array to std?
        std::Array<BasicFormatArgument<State>, sizeof...(Args)> args;

        explicit FormatArgumentStore (std::Array<BasicFormatArgument<State>, sizeof...(Args)> arguments) : args(arguments) { };
    };

    // todo
    template<class State>
    class BasicFormatArguments {
        size_t size { };
        const BasicFormatArgument<State>* data;

    public:
        BasicFormatArguments() noexcept = default;

        template<class... Args>
        BasicFormatArguments(const std::FormatArgumentStore<State, Args...>& store) noexcept
            : size(store.args.size()),
            data(store.args.data()) { }

        // Accessors
        BasicFormatArgument<State> get(std::size_t index) const noexcept {
            // todo: if out of size, return monostate?
            return data[index]; // todo: Switch to array?
        }

        auto count() -> std::size_t {
            return size;
        }
    };

    // Definition
    using FormatArguments = BasicFormatArguments<std::FormatState>;

    // todo
    template<class State = std::FormatState, class... Args>
    std::FormatArgumentStore<State, Args...> makeFormatArguments(Args&&... args) {

        return std::FormatArgumentStore<State, Args...>(
                std::Array<BasicFormatArgument<State>, sizeof...(Args)> {
                        BasicFormatArgument<State>(args)...
                }
        );
    }
}

#endif //HEPHAISTOS_FORMAT_ARGUMENTS_H

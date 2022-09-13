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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_RESULT_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_RESULT_H

#include "utility.h"
#include <concepts>

namespace std {

    struct None { };

    template<class Type, class Error = None>
    struct Result {
    private:
        Type resultValue;
        Error errorValue;
        bool isResult;

        explicit Result(Type result) : resultValue { result }, isResult { true } { }
        explicit Result(Error error) : errorValue { error }, isResult { false } { }
    public:
        explicit Result() = default;

        // Initializers
        static constexpr auto success(Type result) -> Result<Type, Error> {
            return Result(result);
        }

        static constexpr auto failure() -> Result<Type, Error> {
            return Result(Error());
        }

        static constexpr auto failure(Error error) -> Result<Type, Error> {
            return Result(error);
        }

        // Accessors
        [[nodiscard]] constexpr auto get() const noexcept {
            return resultValue;
        }

        template<class Function>
        auto getOr(Function onError) -> Type& {
            if(!isValid()) {
                onError(errorValue);
            }
            return resultValue;
        }

        [[nodiscard]] constexpr auto error() const noexcept {
            return errorValue;
        }

        [[nodiscard]] constexpr bool isValid() const noexcept {
            return isResult;
        }

        [[nodiscard]] constexpr bool isNotValid() const noexcept {
            return !isResult;
        }

        // Functional Interface
        template<class ResultFunction, class ErrorFunction>
        auto onResult(ResultFunction resultFunction, ErrorFunction errorFunction) -> Result<Type, Error>& {
            if(isValid()) {
                resultFunction(resultValue);
            } else {
                errorFunction(errorFunction);
            }
            return *this;
        }

        template<class Function>
        auto onResult(Function function) -> Result<Type, Error>& {
            if(isValid()) {
                function(resultValue);
            }
            return *this;
        }

        template<class Function>
        auto onError(Function function) -> Result<Type, Error>& {
            if(!isValid()) {
                function(errorValue);
            }
            return *this;
        }

        template<class Function>
        constexpr auto map(Function function) -> decltype(auto) {
            if(!isValid()) {
                std::Result<Type, Error>::failure();
            }
            return function(resultValue);
        }
    };
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_RESULT_H

/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaistOS.
 *
 * HephaistOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaistOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "catch2/catch.hpp"
#include "kernel/klibc/stdio.h"

TEST_CASE("Test sprintf parses all format types correctly") {
    using namespace kernel::lib;

    const auto * format = "char: %c percent: %% int: %d int: %i uint: %u";
    char buffer[55];
    const int32_t count = sprintf(buffer, format, 'A', 123, -456456, 42343U);
    CHECK(count == 52);

    CHECK_THAT(buffer, Catch::Matchers::Equals("char: A percent: % int: 123 int: -456456 uint: 42343"));
}

TEST_CASE("Test sprintf parses characters correctly") {
    using namespace kernel::lib;

    const auto * format = "example %cexample exam%cple %c%c test";
    char buffer[34];
    const int32_t count = sprintf(buffer, format, 'a', 'b', 'c', 'd');
    CHECK(count == 33);

    CHECK_THAT(buffer, Catch::Matchers::Equals("example aexample exambple cd test"));
}

TEST_CASE("Test sprintf parses integers and unsigned integers correctly") {
    using namespace kernel::lib;

    const auto * format = "example %d, %d, %u";
    char buffer[24];
    const int32_t count = sprintf(buffer, format, 1, -123, 132432U);
    CHECK(count == 23);

    CHECK_THAT(buffer, Catch::Matchers::Equals("example 1, -123, 132432"));
}
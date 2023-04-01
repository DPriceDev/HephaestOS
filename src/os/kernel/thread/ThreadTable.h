// Copyright (C) 2023 David Price - All Rights Reserved
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

#ifndef HEPHAISTOS_THREADTABLE_H
#define HEPHAISTOS_THREADTABLE_H

#include "thread/model/ThreadControlBlock.h"
#include <array.h>
#include <expected.h>
#include <stdint.h>

namespace kernel {

    class ThreadTable {
        std::Array<ThreadControlBlock*, 10> table {};

      public:
        auto registerThreadControlBlock(/* todo: Make this a unique pointer */ ThreadControlBlock* threadControlBlock)
            -> bool;

        auto getThreadControlBlock(TID tid) -> std::Optional<ThreadControlBlock*>;

        void removeThreadControlBlock(TID tid);
    };
}// namespace kernel

#endif// HEPHAISTOS_THREADTABLE_H

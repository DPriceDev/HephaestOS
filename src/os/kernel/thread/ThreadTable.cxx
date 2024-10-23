// Copyright (C) 2023 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

module;

#include <array.h>

export import os.kernel.thread.control;

export module os.kernel.thread.table;

namespace kernel {

    export class ThreadTable {
        std::Array<ThreadControlBlock*, 10> table {};

    public:
        auto registerThreadControlBlock(/* todo: Make this a unique pointer */ ThreadControlBlock* threadControlBlock)
            -> bool;

        auto getThreadControlBlock(TID tid) -> std::Optional<ThreadControlBlock*>;

        void removeThreadControlBlock(TID tid);
    };
}// namespace kernel


auto kernel::ThreadTable::registerThreadControlBlock(kernel::ThreadControlBlock* block) -> bool {
    auto entry = table.at(block->id);
    if (!entry || entry->get() != nullptr) {
        return false;
    }

    entry->get() = block;
    return true;
}
auto kernel::ThreadTable::getThreadControlBlock(kernel::TID tid) -> std::Optional<ThreadControlBlock*> {
    const auto entry = table.at(tid);
    if (!entry || entry->get() == nullptr) {
        return std::nullOptional;
    }

    return std::Optional<ThreadControlBlock*>(entry->get());
}
void kernel::ThreadTable::removeThreadControlBlock(kernel::TID tid) {
    const auto entry = table.at(tid);
    if (entry) {
        entry->get() = nullptr;
    }
}

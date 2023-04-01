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

#include "ThreadTable.h"
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
        return std::nullOption;
    }

    return std::Optional<ThreadControlBlock*>(entry->get());
}
void kernel::ThreadTable::removeThreadControlBlock(kernel::TID tid) {
    const auto entry = table.at(tid);
    if (entry) {
        entry->get() = nullptr;
    }
}

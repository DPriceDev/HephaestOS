//
// Created by david on 02/04/2021.
//

#ifndef HEPHAIST_OS_KERNEL_LIBRARY_ARRAY_H
#define HEPHAIST_OS_KERNEL_LIBRARY_ARRAY_H

#include "kernel/types.h"

namespace kernel {

    template<typename Type, uint32_t length>
    class Array {
    public:
        Type& at(uint32_t index) {
            return array[index];
        }

        uint32_t size() {
            return length;
        }

    private:
        Type* array[];
    };
}
#endif //HEPHAIST_OS_KERNEL_LIBRARY_ARRAY_H

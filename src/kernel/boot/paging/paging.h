//
// Created by david on 28/11/2021.
//

#ifndef HEPHAISTOS_PAGING_H
#define HEPHAISTOS_PAGING_H

namespace kernel::boot::paging {

    extern "C" void loadPageDirectory(unsigned int *);
    extern "C" void enablePaging();

    void setupPaging();
}

#endif //HEPHAISTOS_PAGING_H

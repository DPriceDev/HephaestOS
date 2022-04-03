add_library(sharedLibCpp INTERFACE
        include/span.h
        include/iterator.h
        include/array.h include/iterators/iteratortraits.h include/memory.h)
target_include_directories(sharedLibCpp INTERFACE include)
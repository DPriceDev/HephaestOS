add_library(sharedLibCpp INTERFACE
        include/span.h
        include/iterator.h
        include/array.h include/iterators/iterator_traits.h include/memory.h include/iterators/reverse_iterator.h include/iterators/iterator_operations.h include/iterators/iterators.h)
target_include_directories(sharedLibCpp INTERFACE include)
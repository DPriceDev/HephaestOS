add_library(sharedLibCpp INTERFACE
        include/span.h
        include/iterator.h
        include/array_base.h
        include/iterators/iterator_traits.h
        include/memory.h
        include/iterators/reverse_iterator.h
        include/iterators/iterator_operations.h
        include/iterators/iterators.h include/algorithm.h
        include/result.h
        include/format_base.h
        include/string_view.h
        include/string
        include/format/formatter/char_formatter.h
        include/charconv.h
        include/iterators/incrementable_traits.h)
target_include_directories(sharedLibCpp INTERFACE include)
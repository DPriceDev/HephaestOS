add_library(sharedLibCpp INTERFACE
        include/span.h
        include/iterator.h
        include/array_base.h
        include/iterators/iterator_traits.h
        include/memory.h
        include/iterators/reverse_iterator.h
        include/iterators/iterator_operations.h
        include/iterators/iterators.h include/algorithms.h
        include/utility.h
        include/result.h
        include/format.h include/string_view.h include/string.h include/format/formatter.h include/format/format_state.h include/format/format_arguments.h include/format/format_argument.h include/variant.h)
target_include_directories(sharedLibCpp INTERFACE include)
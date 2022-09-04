#ifndef D_PRICE_DEV_VARIANT_GET_H
#define D_PRICE_DEV_VARIANT_GET_H

#include "variant_variant.h"

namespace std {

    /**
     * @return the value where the type is the type at the @tparam TypeIndex
     * in the @tparam Types parameter pack. If the @tparam TypeIndex is not the
     * current active Variant Type, an exception is thrown.
     * @tparam Types are the Variants stored in @param variant.
     */
    template<size_t TypeIndex, class... Types>
    constexpr auto getIf(std::Variant<Types...>& variant) -> auto* {
        if(variant.index() != TypeIndex) {
            return nullptr;
        }

        using Type = typename VariantType<TypeIndex, Types...>::type;
        return static_cast<Type*>(variant.data());
    }

    /**
     * @return the value of type @tparam Type from the @tparam Types parameter
     * pack. If the @tparam Type is not the current active Variant Type,
     * an exception is thrown.
     * @tparam Types are the Variants stored in @param variant.
     */
    template<class Type, class... Types>
    constexpr auto getIf(std::Variant<Types...>& variant) -> Type* {
        auto getIndex = VariantIndex<0, Type, Types...>().index;
        if(getIndex != variant.index()) {
            return nullptr;
        }
        return static_cast<Type*>(variant.data());
    }
}

#endif // D_PRICE_DEV_VARIANT_GET_H

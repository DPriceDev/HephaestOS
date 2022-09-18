#ifndef D_PRICE_DEV_VARIANT_VISITOR_H
#define D_PRICE_DEV_VARIANT_VISITOR_H

#include <type_traits>
#include <array.h>
#include <bits/move.h>

#include "parameter_pack.h"
#include "variant_variant.h"
#include "variant_get.h"

namespace std {

    namespace detail {

        /**
         *
         * @tparam Visitor
         * @tparam Variant
         * @tparam Size
         * @tparam FunctionType
         * @tparam Type
         * @tparam Types
         */
        template<class Visitor, class Variant, std::size_t Size, class FunctionType, class Type, class... Types>
        struct VariantVisitorArrayBuilder : public VariantVisitorArrayBuilder<
                Visitor,
                Variant,
                Size - 1,
                std::common_type_t<FunctionType, decltype([] (Visitor &&visitor, Variant &variant) {
                    return visitor(
                            std::get<Type>(variant));
                })>,
                Types...,
                Type
        > { };

        /**
         *
         * @tparam Visitor
         * @tparam Variant
         * @tparam FunctionType
         * @tparam Type
         * @tparam Types
         */
        template<class Visitor, class Variant, class FunctionType, class Type, class... Types>
        struct VariantVisitorArrayBuilder<Visitor, Variant, 0, FunctionType, Type, Types...> {

            static constexpr auto function = [] (Visitor &&visitor, Variant &variant) {
                return visitor(std::get<Type>(variant));
            };

            static constexpr auto array = std::Array<std::common_type_t<FunctionType, decltype(function)>,
                    sizeof...(Types) + 1> {
                    function,
                    [] (Visitor &&visitor, Variant &variant) {
                        return visitor(std::get<Types>(variant));
                    }...
            };
        };

        /**
         *
         * @tparam Visitor
         * @tparam Variant
         * @tparam Size
         * @tparam Type
         * @tparam Types
         */
        template<class Visitor, class Variant, std::size_t Size, class Type, class... Types>
        struct VariantVisitorArray : public VariantVisitorArrayBuilder<
                Visitor,
                Variant,
                Size - 1,
                decltype([] (Visitor &&visitor, Variant &variant) { return visitor(std::get<Type>(variant)); }),
                Types...,
                Type
        > { };

        /**
         *
         * @tparam Visitor
         * @tparam Variant
         * @tparam Types
         * @param variant
         * @return
         */
        template<class Visitor, class Variant, class... Types>
        constexpr auto visit(std::Variant<Types...> &variant) -> decltype(auto) {
            return VariantVisitorArray<Visitor, Variant, sizeof...(Types), Types...>::array;
        }
    }

    /**
     * Visit takes a given variant or variants and applies it to a visitor
     * function. The visitor function will call the corresponding method
     * associated to the active indexes and types in each variant.
     */
    template<class Visitor, class Variant>
    constexpr auto visit(Visitor&& visitor, Variant & variant) -> decltype(auto) {
        auto array = detail::visit<Visitor, Variant>(variant);
        return array[variant.index()](std::forward<Visitor>(visitor), variant);
    }

    /**
     * Visit takes a given variant or variants and applies it to a visitor
     * function. The visitor function will call the corresponding method
     * associated to the active indexes and types in each variant.
     */
    template<class Visitor, class Variant>
    constexpr auto visit(Visitor& visitor, Variant & variant) -> decltype(auto) {
        return std::visit(std::move(visitor), variant);
    }
}

#endif // D_PRICE_DEV_VARIANT_VISITOR_H

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
         * Takes the final set of visitor @tparam Functions constructed from the original
         * set of Variants and maps then to an array of function pointers.
         * This checks the return type is the same for all functions.
         */
        template<class Visitor, class Var, class... Functions, class...Args, class... OrgVariants>
        constexpr auto constructFunctionArray(
                ParameterPack<Args...> /* Unused */,
                ParameterPack<OrgVariants...> /* Unused */,
                Functions... functions
        ) -> decltype(auto) {
            // todo: static_assert( is all the same );
            return std::Array<std::common_type_t<Functions...>, sizeof...(functions)>{functions...};
        }

        /**
         * This method takes a matching set of @tparam Variants and @tparam Types
         * and unwraps both packs as the parameters of the @tparam Visitor using
         * the variants get method.
         */
        template<class Visitor, class... Variants, class... Types>
        constexpr auto callVisitor(
                Visitor &&visitor,
                ParameterPack<Types...> /* Unused */,
                Variants &... variants
        ) -> decltype(auto) {
            return visitor(
                    std::getIf<Types>(variants)...
            );
        }

        /**
         * Takes the current @tparam Types from the set of @Types of a given Variant
         * and uses it to construct a function pointer to the relevant call to visitor.
         * The resulting function is then collected with the passed in @tparam Functions
         * and passed to the next call to construct the next Type in the @tparam Types
         * pack.
         * Calls the Function array construct method when @tparam Types is empty.
         */
        template<class Visitor, class Var, class Type, class... Types,
                    class... Functions, class... Args, class... OrgVariants>
        constexpr auto constructFunctionArray(
                ParameterPack<Args...> &&argPack,
                ParameterPack<OrgVariants...> &&originalVariantsPack,
                Functions... functions
        ) -> decltype(auto) {
            auto function = [](Visitor &&visitor, OrgVariants &... variants) {
                // Call visitor used to append the last Type to the end of Args
                return callVisitor(
                        std::move(visitor),
                        ParameterPack<Args..., Type>{},
                        variants...
                );
            };

            // Call again to construct the next function pointer, or to return the function array.
            return constructFunctionArray<Visitor, Var, Types...>(
                    std::move(argPack),
                    std::move(originalVariantsPack),
                    functions...,
                    function
            );
        }

        /**
         * Constructs a multi-dimensional array where each dimension matches to a variant in
         * the @tparam Variants pack. Each array will construct a new array for each type and
         * pass the type as part of the argument list to be used in the visitor later on.
         * If there is only 1 variant left - passed through as a parameter - it calls the
         * method to construct the function pointers for a given set of @tparam Args and Type.
         */
        template<class Visitor, class... Types, class... Variants, class... Args, class... OrgVariants>
        consteval auto constructVariantArray(
                ParameterType<Visitor>&& visitorType,
                ParameterPack<Args...> argPack,
                ParameterPack<std::Variant<Types...>, Variants...> /* Unused - used to unwrap. */,
                ParameterPack<OrgVariants...>&& originalVariantsPack
        ) -> decltype(auto) {
            if constexpr(sizeof...(Variants) > 0) {
                // If there is more than 1 variant left, extract the Type and map it to an array.
                return std::Array {
                        constructVariantArray(
                                std::move(visitorType),
                                ParameterPack<Args..., Types>{ },
                                ParameterPack<Variants...> { },
                                std::move(originalVariantsPack)
                        )...
                };
            } else {
                // If there is only 1 Variant left, use it to construct the function pointers array.
                return constructFunctionArray<Visitor, std::Variant<Types...>, Types...>(
                        std::move(argPack),
                        std::move(originalVariantsPack)
                );
            }
        }

        /**
         * End of the visit template function which takes just a @param function and a @param visitor
         * once all of the variants have run out.
         * @return the function pointer for the specific set of active variant types.
         */
        template<class Function>
        constexpr auto visit(Function &function) -> decltype(auto) {
            return function;
        }

        /**
         * Visit template walks the
         */
        template<class Array, class Var, class... Variants>
        constexpr auto visit(Array &array, Var &variant, Variants &... variants) -> decltype(auto) {
            return visit(array[variant.index()], variants...);
        }
    }

    /**
     * Takes a set of @tparam Functions and inherits recursively from each function
     * in the Pack. For each function, the operator() is taken and defined to
     * allow the one struct to expose all of the functions as one interface.
     */
    template<class... Functions>
    struct Overloaded : Functions ... {
        using Functions::operator()...;
    };

    /**
     * Constructs an Overloaded set of functions that exposes each operator()
     * method in the same struct.
     */
    template<class... Functions>
    Overloaded(Functions...) -> Overloaded<Functions...>;

    /**
     * Visit takes a given variant or variants and applies it to a visitor
     * function. The visitor function will call the corresponding method
     * associated to the active indexes and types in each variant.
     */
    template<class Visitor, class... Variants>
    constexpr auto visit(Visitor&& visitor, Variants &... variants) -> decltype(auto) {

        // Constructs a multi-dimensional array of function pointers at compile time.
        auto array = detail::constructVariantArray(
                ParameterType<Visitor>{},
                ParameterPack<>{ },
                ParameterPack<Variants...> { },
                ParameterPack<Variants...>{}
        );

        auto function = detail::visit(array, variants...);
        return function(std::forward<Visitor>(visitor), variants...);
    }

    /**
     * Visit takes a given variant or variants and applies it to a visitor
     * function. The visitor function will call the corresponding method
     * associated to the active indexes and types in each variant.
     */
    template<class Visitor, class... Variants>
    constexpr auto visit(Visitor& visitor, Variants &... variants) -> decltype(auto) {
        return std::visit(std::move(visitor), variants...);
    }
}

#endif // D_PRICE_DEV_VARIANT_VISITOR_H

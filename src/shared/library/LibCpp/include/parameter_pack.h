//
// Created by David Price on 26/04/2022.
//

#ifndef VARIANT_VARIANT_PARAMETER_H
#define VARIANT_VARIANT_PARAMETER_H

namespace std {

    /**
     * Parameter Pack allows a set of variadic @tparam Parameters to be passed to a function
     * without it interfering or picking up types from another set of variadic parameters.
     */
    template<class... Parameters>
    struct ParameterPack {
    };

    /**
     * Parameter Type allows a given @tparam Type to be passed to a function as
     * a parameter without interfering with a variadic parameter pack. It also
     * allows the Type to be defined out of order.
     */
    template<class Type>
    struct ParameterType {
    };

}

#endif //VARIANT_VARIANT_PARAMETER_H

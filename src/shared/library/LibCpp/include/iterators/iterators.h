// Copyright (C) 2022 David Price - All Rights Reserved
// This file is part of HephaistOS.
//
// HephaistOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaistOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_ITERATORS_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_ITERATORS_H

#include "iterator_traits.h"
#include <bits/move.h>
#include "memory.h"
#include "utility.h"

namespace std {

    /**
     * Is Reference defines that @tparam Type is a reference type.
     */
    template<class Type>
    concept isReference = requires(Type type) {
        std::is_reference<Type>(type);
    };

    /**
     * Weakly Incrementable defines that Type @tparam Iterator can be incremented using pre and post operators
     * i.e. ++i and i++. Weakly defines that it does not preserve equality, therefore a == b does not mean a++ == b++.
     */
    template<class Type>
    concept weaklyIncrementable =
    std::movable<Type>
    && requires(Type iterator) {
        typename iteratorDifferenceType<Type>;
        // todo: is signed integer like
        { ++iterator } -> std::same_as<Type &>;
        iterator++;
    };

    /**
     * Incrementable defines that Type @tparam Iterator can be incremented using pre and post operators
     * i.e. ++i and i++. it also preserves equality, therefore a == b has the guarantee that a++ == b++.
     */
    template<class Type>
    concept incrementable =
    std::regular<Type>
    && std::weaklyIncrementable<Type>
    && requires (Type type) {
        { type++ } -> std::same_as<Type>;
    };

    /**
     * Input Or Output Iterator is the base @tparam Iterator Type that all Iterators will satisfy.
     * This defines a @tparam Iterator is incrementable, without preserving equality, and that
     * the @tparam Iterator can be de-referenced into a referencable type.
     */
    template<class Iterator>
    concept inputOrOutputIterator = requires(Iterator iterator) {
        *iterator;
        //{ *iterator } -> std::same_as<Iterator&>; // todo: Need to define referencable, i.e. not void?
    } && std::weaklyIncrementable<Iterator>;

    /**
     * Defines a @tparam Type that can be "read" by calling the * operator. This requires that the
     * "read" type is a reference type of @tparam Type.
     * Also the l-value & and r-value && Types must be of the same reference type.
     */
    template<class Type>
    concept indirectlyReadable =
            requires(const Type type) {
                typename std::iteratorValueType<Type>;
                typename std::iteratorReferenceType<Type>;
                { *type } -> std::same_as<std::iteratorReferenceType<Type>>;
            }
            && std::common_reference_with<Type&&, Type&>
            && std::common_reference_with<Type&&, Type&&>
            && std::common_reference_with<Type&&, const Type&>;

    /**
     * todo comment
     * @tparam Output
     * @tparam Type
     */
    template<class Output, class Type>
    concept indirectlyWritable =
    requires(Output&& output, Type&& type) {
        *output = std::forward<Type>(type);
        *std::forward<Output>(output) = std::forward<Type>(type);
        const_cast<const std::iteratorReferenceType<Output>&&>(*output) = std::forward<Type>(type);
        const_cast<const std::iteratorReferenceType<Output>&&>(*std::forward<Output>(output)) = std::forward<Type>(type);
    };

    /**
     * todo comment
     * @tparam Iterator
     */
     template<class Iterator, class Type>
     concept outputIterator =
        std::inputOrOutputIterator<Iterator>
        && std::indirectlyWritable<Iterator, Type>
        && requires(Iterator iterator, Type&& type) {
            *iterator++ = std::forward<Type>(type);
        };


    /**
     * Input iterator defines an @tparam Iterator that extends an Input or Output Iterator
     * with the restriction that it can use operator * to allow the Iterator to be read.
     */
    template<class Iterator>
    concept inputIterator =
    std::inputOrOutputIterator<Iterator>
    && std::indirectlyReadable<Iterator>;

    /**
     * Sentinel For defines the type @tparam Sentinel can act as the last "sentinel" Type in a range of
     * @tparam Iterator - i.e. [i to s] where i is the iterator and s is the terminating sentinel.
     * This requires that i == s is defined, that the sentinel is copyable, and the iterator can be de-referenced.
     */
    template<class Iterator, class Sentinel>
    concept sentinelFor =
    std::semiregular<Sentinel>
    && std::inputOrOutputIterator<Iterator>
    && std::equality_comparable_with<Iterator, Sentinel>;

    /**
     * Forward iterator defines an @tparam Iterator that extends an Input Iterator, and is incrementable,
     * guaranteeing that i and i++ are of the same type and can be compared.
     */
    template<class Iterator>
    concept forwardIterator =
    std::inputIterator<Iterator>
    && std::incrementable<Iterator>
    && std::sentinelFor<Iterator, Iterator>;

    /**
     * Bidirectional Iterator defines an @tparam Iterator that extends the forward iterator, but also supports
     * decrementing and guarantees that a decremented value is the same type as @tparam Iterator.
     * @tparam Iterator
     */
    template<class Iterator>
    concept bidirectionalIterator =
    std::forwardIterator<Iterator>
    && requires(Iterator iterator) {
        { --iterator } -> std::same_as<Iterator&>;
        { iterator-- } -> std::same_as<Iterator>;
    };

    template<class Iterator, class Sentinel>
    inline constexpr bool disable_sized_sentinel_for = false;

    /**
     * Sentinel For defines the type @tparam Sentinel extends the sentinelFor concept to define
     * that the @tparam Sentinel provides the correct difference as the @tparam Iterator.
     */
    template<class Iterator, class Sentinel>
    concept sizedSentinelFor =
    std::sentinelFor<Iterator, Sentinel>
    && !disable_sized_sentinel_for<std::remove_cv_t<Iterator>, std::remove_cv_t<Sentinel>>
    && requires(const Iterator& iterator, const Sentinel& sentinel) {
        { sentinel - iterator } -> std::same_as<std::iteratorDifferenceType<Iterator>>;
        { iterator - sentinel } -> std::same_as<std::iteratorDifferenceType<Iterator>>;
    };

    /**
     * Random Access Iterator defines an @tparam Iterator that extends the Bidirectional iterator.
     * It defines the requirement that ==,!=,<,>,<=,>= operations on the type will match what is
     * expected for a type that is strictly ordered, i.e. 0 1 2 3 4, 3 < 4, 5 > 2, etc.
     * It also defines that the difference type between an iterator and the end of a range
     * (sentinel) is the same for both, and that the @tparam Iterator type does not change when
     * decrements or increments more than 1 are made.
     */
    template<class Iterator>
    concept randomAccessIterator =
    std::bidirectionalIterator<Iterator>
    && std::totally_ordered<Iterator>
    && std::sizedSentinelFor<Iterator, Iterator>
    && requires(
            Iterator iterator,
            const Iterator constIterator,
            const std::iteratorDifferenceType<Iterator> difference
    ) {
        { iterator += difference } -> std::same_as<Iterator&>;
        { constIterator + difference } -> std::same_as<Iterator>;
        { difference + constIterator } -> std::same_as<Iterator>;
        { iterator -= difference } -> std::same_as<Iterator&>;
        { constIterator - difference } -> std::same_as<Iterator>;
        {  constIterator[difference]  } -> std::same_as<std::iteratorReferenceType<Iterator>>;
    };

    /**
     * Random Access Iterator defines an @tparam Iterator that extends the randomAccessIterator
     * iterator, and adds the guarantee that the range being iterated over is contiguous in
     * memory.
     */
    template<class Iterator>
    concept contiguousIterator =
    std::randomAccessIterator<Iterator>
    && std::is_lvalue_reference_v<Iterator&>
    && std::same_as<
            std::iteratorValueType<Iterator>,
            std::remove_cvref_t<iteratorReferenceType<Iterator>>
    >
    && requires(const Iterator& iterator) {
        { std::toAddress(iterator) } ->
        std::same_as<std::add_pointer_t<std::iteratorReferenceType<Iterator>>>;
    };
};

#endif // HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_ITERATORS_H

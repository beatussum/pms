/*
 * Copyright (C) 2022 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */


#ifndef PMSCORE_CORE_TYPE_TRAITS_HPP
#define PMSCORE_CORE_TYPE_TRAITS_HPP

namespace pmscore
{
    namespace detail
    {
        /************************
         * add_*value_reference *
         ************************/

        template <class _T>
        struct type_identity
        {
            using type = _T;
        };

        template <class _T>
        type_identity<_T&> try_add_lvalue_reference(int);

        template <class _T>
        type_identity<_T> try_add_lvalue_reference(long);

        template <class _T>
        type_identity<_T&&> try_add_rvalue_reference(int);

        template <class _T>
        type_identity<_T> try_add_rvalue_reference(long);

        /***********
         * declval *
         ***********/

        template <class _T, class = _T&&>
        _T&& declval(int);

        template <class _T>
        _T declval(long);

        template <class>
        struct protector
        {
            static constexpr bool stop = false;
        };
    }

    /*********************
     * integral_constant *
     *********************/

    template <class _T, _T _v>
    class integral_constant
    {
    public:
        using type       = integral_constant;
        using value_type = _T;
    public:
        static constexpr _T value = _v;
    public:
        constexpr operator value_type() const noexcept { return value; }
        constexpr value_type operator()() const noexcept { return value; }
    };

    template <bool _v>
    using bool_constant = integral_constant<bool, _v>;

    using false_type = bool_constant<false>;
    using true_type  = bool_constant<true>;

    /*************
     * add_const *
     *************/

    template <class _T>
    struct add_const
    {
        using type = const _T;
    };

    template <class _T>
    using add_const_t = typename add_const<_T>::type;

    /************************
     * add_*value_reference *
     ************************/

    template <class _T>
    struct add_lvalue_reference
        : decltype(detail::try_add_lvalue_reference<_T>(0))
    {};

    template <class _T>
    using add_lvalue_reference_t = typename add_lvalue_reference<_T>::type;

    template <class _T>
    struct add_rvalue_reference
        : decltype(detail::try_add_rvalue_reference<_T>(0))
    {};

    template <class _T>
    using add_rvalue_reference_t = typename add_rvalue_reference<_T>::type;

    /***************
     * conditional *
     ***************/

    template <bool _b, class _A, class _B>
    struct conditional
    {
        using type = _A;
    };

    template <class _A, class _B>
    struct conditional<false, _A, _B>
    {
        using type = _B;
    };

    template <bool _b, class _A, class _B>
    using conditional_t = typename conditional<_b, _A, _B>::type;

    /***************
     * conjunction *
     ***************/

    template <class...>
    struct conjunction : true_type {};

    template <class _A>
    struct conjunction<_A> : _A {};

    template <class _A, class... _B>
    struct conjunction<_A, _B...>
        : conditional_t<bool(_A::value), conjunction<_B...>, _A>
    {};

    template<class... _B>
    constexpr bool conjunction_v = conjunction<_B...>::value;

    /***********
     * declval *
     ***********/

    template <class _T>
    constexpr decltype(detail::declval<_T>(0)) declval() noexcept;

    /**********************
     * is_*_constructible *
     **********************/

    template <class _T, class... _Args>
    struct is_nothrow_constructible
        : bool_constant<noexcept(_T(declval<_Args>()...))>
    {};

    template <class _T, class... _Args>
    constexpr bool is_nothrow_constructible_v =
        is_nothrow_constructible<_T, _Args...>::value;

    template <class _T>
    struct is_nothrow_copy_constructible
        : is_nothrow_constructible<_T, add_lvalue_reference_t<add_const_t<_T>>>
    {};

    template <class _T>
    constexpr bool is_nothrow_copy_constructible_v =
        is_nothrow_copy_constructible<_T>::value;

    template <class _T>
    struct is_nothrow_default_constructible : is_nothrow_constructible<_T> {};

    template <class _T>
    constexpr bool is_nothrow_default_constructible_v =
        is_nothrow_default_constructible<_T>::value;

    template <class _T>
    struct is_nothrow_move_constructible
        : is_nothrow_constructible<_T, add_rvalue_reference_t<_T>>
    {};

    template <class _T>
    constexpr bool is_nothrow_move_constructible_v =
        is_nothrow_move_constructible<_T>::value;

    /***********************
     * is_lvalue_reference *
     ***********************/

    template <class _T>
    struct is_lvalue_reference : false_type {};

    template <class _T>
    struct is_lvalue_reference<_T&> : true_type {};

    template <class _T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<_T>::value;

    /***********
     * is_same *
     ***********/

    template <class _A, class _B>
    struct is_same : false_type {};

    template <class _T>
    struct is_same<_T, _T> : true_type {};

    template <class _A, class _B>
    constexpr bool is_same_v = is_same<_A, _B>::value;

    /********************
     * remove_reference *
     ********************/

    template <class _T>
    struct remove_reference
    {
        using type = _T;
    };

    template <class _T>
    struct remove_reference<_T&>
    {
        using type = _T;
    };

    template <class _T>
    struct remove_reference<_T&&>
    {
        using type = _T;
    };

    template <class _T>
    using remove_reference_t = typename remove_reference<_T>::type;
}

#include "core/type_traits.ipp"

#endif // PMSCORE_CORE_TYPE_TRAITS_HPP

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

    using false_type = integral_constant<bool, false>;
    using true_type  = integral_constant<bool, true>;

    /***********************
     * is_lvalue_reference *
     ***********************/

    template <class>
    struct is_lvalue_reference : false_type {};

    template <class _T>
    struct is_lvalue_reference<_T&> : true_type {};

    template <class _T>
    constexpr bool is_lvalue_reference_v = is_lvalue_reference<_T>::value;

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

#endif // PMSCORE_CORE_TYPE_TRAITS_HPP

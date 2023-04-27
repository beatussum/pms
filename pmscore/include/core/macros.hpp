/*
 * Copyright (C) 2022-2023 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
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


#ifndef PMSCORE_CORE_MACROS_HPP
#define PMSCORE_CORE_MACROS_HPP

#include "core/type_traits.hpp"

namespace pmscore::detail
{
    /***************
     * noexcept_cm *
     ***************/

    template <class _T>
    struct is_nothrow_cm_constructible
        : bool_constant<
            is_nothrow_copy_constructible_v<_T> &&
            is_nothrow_move_constructible_v<_T>
        >
    {};

    template <class... _T>
    struct are_nothrow_cm_constructible
        : conjunction<is_nothrow_cm_constructible<_T>...>
    {};

    /****************
     * noexcept_def *
     ****************/

    template <class... _T>
    struct are_nothrow_default_constructible
        : conjunction<is_nothrow_default_constructible<_T>...>
    {};

    /****************
     * noexcept_mov *
     ****************/

    template <class... _T>
    struct are_nothrow_move_constructible
        : conjunction<is_nothrow_move_constructible<_T>...>
    {};

    /***************
     * noexcept_pf *
     ***************/

    template <class _T>
    struct is_noexcept_pf
        : conditional_t<
            is_same_v<_T, add_lvalue_reference_t<add_const_t<_T>>>,
            is_nothrow_copy_constructible<_T>,

            conditional_t<
                is_same_v<_T, add_rvalue_reference_t<_T>>,
                is_nothrow_move_constructible<_T>,
                false_type
            >
        >
    {};

    template <class... _T>
    struct are_noexcept_pf : conjunction<is_noexcept_pf<_T>...> {};
}

#define noexcept_cm(...)                                               \
    noexcept(detail::are_nothrow_cm_constructible<__VA_ARGS__>::value)

#define noexcept_def(...)                                                   \
    noexcept(detail::are_nothrow_default_constructible<__VA_ARGS__>::value)

#define noexcept_mov(...)                                                \
    noexcept(detail::are_nothrow_move_constructible<__VA_ARGS__>::value)

#define noexcept_pf(...) noexcept(detail::are_noexcept_pf<__VA_ARGS__>::value)

#define noexcept_if(__predicate) noexcept(noexcept(__predicate))

#endif // PMSCORE_CORE_MACROS_HPP

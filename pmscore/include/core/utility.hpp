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


#ifndef PMSCORE_CORE_UTILITY_HPP
#define PMSCORE_CORE_UTILITY_HPP

#include "core/type_traits.hpp"

/***********
 * forward *
 ***********/

template <class _T>
constexpr _T&& forward(remove_reference_t<_T>&) noexcept;

template <class _T>
constexpr _T&& forward(remove_reference_t<_T>&&) noexcept;

/********
 * pair *
 ********/

template <class _First, class _Second = _First>
class pair
{
public:
    using first_type  = _First;
    using second_type = _Second;
public:
    _First  first;
    _Second second;
};

#include "core/utility.ipp"

#endif // PMSCORE_CORE_UTILITY_HPP

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


#ifndef PMSCORE_CORE_UTILITY_HPP
#define PMSCORE_CORE_UTILITY_HPP

#include "core/type_traits.hpp"

namespace pmscore
{
    /***********
     * forward *
     ***********/

    template <class _T>
    constexpr _T&& forward(remove_reference_t<_T>& __t) noexcept
        { return static_cast<_T&&>(__t); }

    template <class _T>
    constexpr _T&& forward(remove_reference_t<_T>&&) noexcept;

    /********
     * move *
     ********/

    template <class _T>
    constexpr remove_reference_t<_T>&& move(_T&& __t) noexcept
        { return static_cast<remove_reference_t<_T>&&>(__t); }
}

#include "core/utility.ipp"

#endif // PMSCORE_CORE_UTILITY_HPP

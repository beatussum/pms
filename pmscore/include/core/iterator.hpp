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


#ifndef PMSCORE_CORE_ITERATOR_HPP
#define PMSCORE_CORE_ITERATOR_HPP

#include <stddef.h>

namespace pmscore
{
    template <class _T, size_t _n>
    constexpr _T* begin(_T (&__array)[_n]) noexcept { return &__array[0]; }

    template <class _T, size_t _n>
    constexpr _T* end(_T (&__array)[_n]) noexcept { return &__array[_n]; }

    template <class _InputIt, class _OutputIt>
    _OutputIt copy(_InputIt __afirst, _InputIt __alast, _OutputIt __bfirst);
}

#include "core/iterator.ipp"

#endif // PMSCORE_CORE_ITERATOR_HPP

/*
 * Copyright (C) 2022 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
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


#include "vector.hpp"

#include "../core/core.hpp"

namespace math
{
    using namespace core;

    vector::operator String() const
    {
        return '{'_s + m_x + ", "_s + m_y + ", "_s + m_z + '}'_s;
    }

    /************************
     * Comparison operators *
     ************************/

    constexpr bool operator==(const vector& __a, const vector& __b) noexcept
    {
        return
            (__a.m_x == __b.m_x) &&
            (__a.m_y == __b.m_y) &&
            (__a.m_z == __b.m_z);
    }

    constexpr bool operator!=(const vector& __a, const vector& __b) noexcept
    {
        return !(__a == __b);
    }

    /************************
     * Arithmetic operators *
     ************************/

    constexpr vector vector::operator+() noexcept
    {
        return *this;
    }

    constexpr vector vector::operator-() noexcept
    {
        return vector(-m_x, -m_y, -m_z);
    }

    constexpr vector operator+(const vector& __a, const vector& __b) noexcept
    {
        return vector(__a.m_x + __b.m_x, __a.m_y + __b.m_y, __a.m_z + __b.m_z);
    }

    constexpr vector operator-(const vector& __a, const vector& __b) noexcept
    {
        return __a + (-__b);
    }

    /************************
     * Assignment operators *
     ************************/

    vector vector::operator+=(const vector& __b) noexcept
    {
        return *this = (*this + __b);
    }

    vector vector::operator-=(const vector& __b) noexcept
    {
        return *this = (*this - __b);
    }
}

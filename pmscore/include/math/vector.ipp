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


namespace pmscore
{
    /************************
     * Comparison operators *
     ************************/

    constexpr bool operator==(const vector& __a, const vector& __b) noexcept
    {
        return (__a.x == __b.x) && (__a.y == __b.y);
    }

    constexpr bool operator!=(const vector& __a, const vector& __b) noexcept
    {
        return !(__a == __b);
    }

    /************************
     * Arithmetic operators *
     ************************/

    constexpr vector vector::operator+() const noexcept
    {
        return *this;
    }

    constexpr vector vector::operator-() const noexcept
    {
        return {-x, -y};
    }

    constexpr vector vector::operator/(real __b) const
    {
        return {x / __b, y / __b};
    }

    constexpr vector operator+(const vector& __a, const vector& __b) noexcept
    {
        return {__a.x + __b.x, __a.y + __b.y};
    }

    constexpr vector operator-(const vector& __a, const vector& __b) noexcept
    {
        return __a + (-__b);
    }

    constexpr vector operator*(real __a, const vector& __b) noexcept
    {
        return {__a * __b.x, __a * __b.y};
    }

    /*************************
     * Arithmetic operations *
     *************************/

    constexpr real dot(const vector& __a, const vector& __b) noexcept
    {
        return __a.x * __b.x + __a.y * __b.y;
    }

    /********************************
     * Member arithmetic operations *
     ********************************/

    constexpr real vector::dot(const vector& __b) const noexcept
    {
        return pmscore::dot(*this, __b);
    }

    /************************
     * Assignment operators *
     ************************/

    constexpr vector& vector::operator+=(const vector& __b) noexcept
    {
        return *this = (*this + __b);
    }

    constexpr vector& vector::operator-=(const vector& __b) noexcept
    {
        return *this = (*this - __b);
    }

    constexpr vector& vector::operator*=(real __a) noexcept
    {
        return *this = (__a * *this);
    }

    constexpr vector& vector::operator/=(real __b)
    {
        return *this = (*this / __b);
    }
}

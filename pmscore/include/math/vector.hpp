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


#ifndef PMSCORE_MATH_VECTOR_HPP
#define PMSCORE_MATH_VECTOR_HPP

#include "math/math.hpp"

#include <Arduino.h>

namespace pmscore
{
    class vector;

    /************************
     * Comparison operators *
     ************************/

    constexpr bool operator==(const vector&, const vector&) noexcept;
    constexpr bool operator!=(const vector&, const vector&) noexcept;

    /************************
     * Arithmetic operators *
     ************************/

    constexpr vector operator+(const vector&, const vector&) noexcept;
    constexpr vector operator-(const vector&, const vector&) noexcept;
    constexpr vector operator*(real, const vector&) noexcept;
    constexpr vector operator/(const vector&, real);
    constexpr real dot(const vector&, const vector&) noexcept;

    class vector
    {
    public:
        static vector with_polar_coordinates(real __r, real __angle);
        static vector with_polar_coordinates(real __angle);
    public:
        explicit operator String() const;
    public:
        real angle() const noexcept { return atan2(y, x); }
        real norm() const noexcept { return sqrt(sq(x) + sq(y)); }
        vector unit() const { return (*this / norm()); }
    public:
        /************************
         * Arithmetic operators *
         ************************/

        constexpr vector operator+() const noexcept;
        constexpr vector operator-() const noexcept;

        /************************
         * Assignment operators *
         ************************/

        constexpr vector& operator+=(const vector&) noexcept;
        constexpr vector& operator-=(const vector&) noexcept;
        constexpr vector& operator*=(real) noexcept;
        constexpr vector& operator/=(real);
        constexpr real dot(const vector&) const noexcept;
    public:
        real x = 0.;
        real y = 0.;
    };
}

#include "math/vector.ipp"

#endif // PMSCORE_MATH_VECTOR_HPP

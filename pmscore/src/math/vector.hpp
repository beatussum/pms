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


#ifndef PMSCORE_MATH_VECTOR_HPP
#define PMSCORE_MATH_VECTOR_HPP

#include "math.hpp"

class String;

namespace math
{
    class vector
    {
        /************************
         * Comparison operators *
         ************************/

        friend constexpr bool operator==(
            const vector&,
            const vector&
        ) noexcept;

        friend constexpr bool operator!=(
            const vector&,
            const vector&
        ) noexcept;

        /************************
         * Arithmetic operators *
         ************************/

        friend constexpr vector operator+(
            const vector&,
            const vector&
        ) noexcept;

        friend constexpr vector operator-(
            const vector&,
            const vector&
        ) noexcept;
    public:
        constexpr vector(real __x = 0., real __y = 0., real __z = 0.) noexcept
            : m_x(__x)
            , m_y(__y)
            , m_z(__z)
        {}
    public:
        explicit operator String() const;
    public:
        /************************
         * Arithmetic operators *
         ************************/

        constexpr vector operator+() noexcept;
        constexpr vector operator-() noexcept;

        /************************
         * Assignment operators *
         ************************/

        vector operator+=(const vector&) noexcept;
        vector operator-=(const vector&) noexcept;
    private:
        real m_x, m_y, m_z;
    };
}

#endif // PMSCORE_MATH_VECTOR_HPP

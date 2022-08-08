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


#ifndef PMSCORE_SPEED_PROFILE_TRAPEZOIDAL_HPP
#define PMSCORE_SPEED_PROFILE_TRAPEZOIDAL_HPP

#include "core/utility.hpp"

#include <Arduino.h>

namespace pmscore::speed_profile
{
    template <class _Distance>
    class trapezoidal
    {
    public:
        using distance_type = _Distance;
    public:
        explicit constexpr trapezoidal(
            real __a,
            real __epsilon,
            uint8_t __m_0,
            uint8_t __m_f,
            uint8_t __M,
            _Distance&& __d = _Distance()
        )
            : m_a(__a)
            , m_epsilon(__epsilon)
            , m_m_0(__m_0)
            , m_m_f(__m_f)
            , m_M(__M)
            , m_distance(forward<_Distance>(__d))
            , m_is_increasing(false)
            , m_is_triangular(false)
            , m_x_0(0.)
            , m_x_f(0.)
            , m_x_1(0.)
            , m_x_2(0.)
        {}

        explicit constexpr trapezoidal(
            real __a,
            real __epsilon,
            uint8_t __m_0,
            uint8_t __m_f,
            _Distance&& __d = _Distance()
        )
            : trapezoidal(
                __a,
                __epsilon,
                __m_0,
                __m_f,
                0,
                forward<_Distance>(__d)
            )
        {}
    public:
        bool init(real __x_0, real __x_f) noexcept;
        bool init(real __x_0, real __x_f, uint8_t __M) noexcept;
        int16_t compute_speed(real __x) noexcept;
    private:
        real          m_a;
        real          m_epsilon;
        uint8_t       m_m_0;
        uint8_t       m_m_f;
        uint8_t       m_M;
        distance_type m_distance;

        bool m_is_increasing;
        bool m_is_triangular;

        real m_x_0;
        real m_x_f;

        union
        {
            struct
            {
                real m_x_1;
                real m_x_2;
            };

            real m_x_3;
        };
    };
}

#include "speed_profile/trapezoidal.ipp"

#endif // PMSCORE_SPEED_PROFILE_TRAPEZOIDAL_HPP

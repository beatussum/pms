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

#include "core/core.hpp"
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
        explicit trapezoidal(
            real __a,
            real __epsilon,
            int16_t __m_0,
            int16_t __m_f,
            int16_t __M,
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

        explicit trapezoidal(
            real __a,
            real __epsilon,
            int16_t __m_0,
            int16_t __m_f,
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
        bool init(real __x_0, real __x_f, int16_t __M) noexcept;
        int16_t compute_speed(real __x) noexcept;
    public:
        real get_a() const noexcept { return m_a; }
        void set_a(real __a) noexcept { m_a = __a; }

        real get_epsilon() const noexcept { return m_epsilon; }
        void set_epsilon(real __e) noexcept { m_epsilon = __e; }

        int16_t get_m_0() const noexcept { return m_m_0; }
        void set_m_0(int16_t __m) noexcept { m_m_0 = __m; }

        int16_t get_m_f() const noexcept { return m_m_f; }
        void set_m_f(int16_t __m) noexcept { m_m_f = __m; }

        int16_t get_M() const noexcept { return m_M; }
        void set_M(int16_t __M) noexcept { m_M = __M; }

        distance_type get_distance() const { return m_distance; }
        distance_type set_distance(distance_type);

        bool is_increasing() const noexcept { return m_is_increasing; }
        bool is_triangular() const noexcept { return m_is_triangular; }

        real get_x_0() const noexcept { return m_x_0; }
        real get_x_f() const noexcept { return m_x_f; }
        real get_x_1() const noexcept { return m_x_1; }
        real get_x_2() const noexcept { return m_x_2; }
        real get_x_3() const noexcept { return m_x_3; }
    private:
        real          m_a;
        real          m_epsilon;
        int16_t       m_m_0;
        int16_t       m_m_f;
        int16_t       m_M;
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

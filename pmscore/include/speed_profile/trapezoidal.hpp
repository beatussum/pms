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
#include "core/macros.hpp"
#include "core/utility.hpp"

#include <Arduino.h>

/**
 * @file
 *
 * @brief Ce fichier implémente un profil de vitesse trapézoïdal.
 */

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
            int16_t __m_0,
            int16_t __m_f,
            int16_t __M
        ) noexcept_def(_Distance)
            : m_a(__a)
            , m_epsilon(__epsilon)
            , m_m_0(__m_0)
            , m_m_f(__m_f)
            , m_M(__M)
            , m_distance()
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
            int16_t __m_0,
            int16_t __m_f,
            int16_t __M,
            _Distance&& __d
        ) noexcept_pf(_Distance)
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
    public:
        constexpr bool init(real __x_0, real __x_f) noexcept;
        constexpr int16_t compute_speed(real __x) noexcept;
    public:
        constexpr real get_a() const noexcept { return m_a; }
        constexpr void set_a(real __a) noexcept { m_a = __a; }

        constexpr real get_epsilon() const noexcept { return m_epsilon; }
        constexpr void set_epsilon(real __e) noexcept { m_epsilon = __e; }

        constexpr int16_t get_m_0() const noexcept { return m_m_0; }
        constexpr void set_m_0(int16_t __m) noexcept { m_m_0 = __m; }

        constexpr int16_t get_m_f() const noexcept { return m_m_f; }
        constexpr void set_m_f(int16_t __m) noexcept { m_m_f = __m; }

        constexpr int16_t get_M() const noexcept { return m_M; }
        constexpr void set_M(int16_t __M) noexcept { m_M = __M; }

        constexpr distance_type get_distance()
        const noexcept_mov(distance_type)
            { return m_distance; }

        constexpr void set_distance(distance_type __d)
        noexcept_cm(distance_type)
            { m_distance = move(__d); }

        constexpr bool is_increasing() const noexcept
            { return m_is_increasing; }

        constexpr bool is_triangular() const noexcept
            { return m_is_triangular; }

        constexpr real get_x_0() const noexcept { return m_x_0; }
        constexpr real get_x_f() const noexcept { return m_x_f; }
        constexpr real get_x_1() const noexcept { return m_x_1; }
        constexpr real get_x_2() const noexcept { return m_x_2; }
        constexpr real get_x_3() const noexcept { return m_x_3; }
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

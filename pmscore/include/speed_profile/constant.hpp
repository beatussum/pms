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


#ifndef PMSCORE_SPEED_PROFILE_CONSTANT_HPP
#define PMSCORE_SPEED_PROFILE_CONSTANT_HPP

#include "core/core.hpp"
#include "core/macros.hpp"
#include "core/utility.hpp"
#include "math/math.hpp"

/**
 * @file
 *
 * @brief Ce fichier implémente un profil de vitesse constant.
 */

namespace pmscore::speed_profile
{
    template <class _Distance>
    class constant
    {
    public:
        using distance_type = _Distance;
    public:
        explicit constexpr constant(
            real __epsilon,
            int16_t __M
        ) noexcept_def(_Distance)
            : m_epsilon(__epsilon)
            , m_M(__M)
            , m_distance()
        {}

        explicit constexpr constant(
            real __epsilon,
            int16_t __M,
            _Distance __d
        ) noexcept_cm(_Distance)
            : m_epsilon(__epsilon)
            , m_M(__M)
            , m_distance(move(__d))
        {}
    public:
        constexpr bool init(real __x_0, real __x_f) noexcept;
        constexpr int16_t compute_speed(real __x) noexcept;
    public:
        constexpr real get_epsilon() const noexcept { return m_epsilon; }
        constexpr void set_epsilon(real __e) noexcept { m_epsilon = __e; }

        constexpr int16_t get_M() const noexcept { return m_M; }
        constexpr void set_M(int16_t __M) noexcept { m_M = __M; }

        constexpr distance_type get_distance()
        const noexcept_mov(distance_type)
            { return m_distance; }

        constexpr void set_distance(distance_type __d)
        noexcept_cm(distance_type)
            { m_distance = move(__d); }
    public:
        constexpr bool is_increasing() const noexcept
            { return m_is_increasing; }
    private:
        real          m_epsilon;
        int16_t       m_M;
        distance_type m_distance;

        bool m_is_increasing;

        real m_x_0;
        real m_x_f;
    };
}

#include "speed_profile/constant.ipp"

#endif // PMSCORE_SPEED_PROFILE_CONSTANT_HPP

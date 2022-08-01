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


#ifndef PMSCORE_SPEED_PROFILE_TRIANGULAR_HPP
#define PMSCORE_SPEED_PROFILE_TRIANGULAR_HPP

#include "core/pair.hpp"
#include "math/math.hpp"

#include <stdint.h>

namespace speed_profile
{
    class triangular
    {
    public:
        using return_type = pair<int16_t>;
    public:
        explicit constexpr triangular(real __a, int16_t __omega_a) noexcept
            : m_a(__a)
            , m_omega_a(__omega_a)
            , m_alpha_0(0.)
            , m_alpha_f(0.)
            , m_alpha_1(0.)
            , m_is_ended(false)
            , m_is_turning_left(false)
        {}
    public:
        constexpr return_type default_speed() const noexcept;

        void init(real __alpha_0, real __alpha_f) noexcept;
        return_type compute_speed(real __rangle) noexcept;
    public:
        bool is_ended() const noexcept { return m_is_ended; }
    private:
        real    m_a;
        int16_t m_omega_a;

        real m_alpha_0;
        real m_alpha_f;
        real m_alpha_1;
        bool m_is_ended;
        bool m_is_turning_left;
    };
}

#endif // PMSCORE_SPEED_PROFILE_TRIANGULAR_HPP

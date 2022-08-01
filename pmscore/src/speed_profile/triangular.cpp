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


#include "speed_profile/triangular.hpp"

#include <Arduino.h>

namespace pmscore::speed_profile
{
    constexpr triangular::return_type
    triangular::default_speed() const noexcept
    {
        return {m_omega_a, m_omega_a};
    }

    void triangular::init(real __alpha_0, real __alpha_f) noexcept
    {
        m_alpha_0         = __alpha_0;
        m_alpha_f         = __alpha_f;
        m_alpha_1         = (m_alpha_0 + m_alpha_f) / 2;
        m_is_ended        = false;
        m_is_turning_left = (m_alpha_0 < m_alpha_f);
    }

    triangular::return_type triangular::compute_speed(real __rangle) noexcept
    {
        if (__rangle <= m_alpha_0) {
            return default_speed();
        } else if (__rangle >= m_alpha_f) {
            m_is_ended = true;

            return default_speed();
        } else {
            int16_t k;

            if (__rangle <= m_alpha_1) {
                k = min(round(m_a * (__rangle - m_alpha_0)), 255 - m_omega_a);
            } else {
                k = min(round(m_a * (m_alpha_f - __rangle)), 255 - m_omega_a);
            }

            if (m_is_turning_left) {
                return {m_omega_a - k, m_omega_a + k};
            } else {
                return {m_omega_a + k, m_omega_a - k};
            }
        }
    }
}

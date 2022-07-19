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


#include "arduino/arduino.hpp"
#include "core/core.hpp"

namespace position
{
    template <size_t _n>
    theoretical_computer<_n>::theoretical_computer(const vector (&__path)[_n])
        : m_pos()
        , m_i(&m_path[0])
        , m_current_path(__path[0].norm())
        , m_path_angle(__path[0].angle())
        , m_la(0.)
        , m_lb(0.)
    {
        copy(begin(__path), end(__path), begin(m_path));
    }

    template <size_t _n>
    void theoretical_computer<_n>::update_status(
        real __angle_a,
        real __angle_b
    )
    {
        using namespace arduino;

        real v = (kr / 2) * ((__angle_a - m_la) + (__angle_b - m_lb));

        m_pos += {v * cos(m_path_angle), v * sin(m_path_angle)};

        m_la = __angle_a;
        m_lb = __angle_b;

        if ((m_current_path -= v) <= 0) {
            if (++m_i == end(m_path)) {
                m_i = begin(m_path);
            }

            m_current_path = m_i->norm();
            m_path_angle   = m_i->angle();
        }
    }
}

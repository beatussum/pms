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


#include "position/real_computer.hpp"

#include "arduino/arduino.hpp"

namespace position
{
    void real_computer::update_status(real __angle_a, real __angle_b)
    {
        using namespace arduino;

        real v  = (kr / 2) * ((__angle_a - m_la) + (__angle_b - m_lb));
        m_alpha = (kr / (2 * kd)) * (m_lb - m_la);

        m_pos += {-v * sin(m_alpha), v * cos(m_alpha)};

        m_la = __angle_a;
        m_lb = __angle_b;
    }
}

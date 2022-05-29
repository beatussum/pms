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


#include "position_computer.hpp"

#include "../arduino/encoder.hpp"

namespace path
{
    void position_computer::operator()()
    {
        using namespace arduino;

        (*m_enca)(), (*m_encb)();

        auto a = m_enca->angle(), b = m_encb->angle();

        auto v     = (kr / 2) * ((a - m_la) + (b - m_lb));
        auto alpha = (kr / (2 * kd)) * (m_lb - m_la);

        m_pos += vector(-v * sin(alpha), v * cos(alpha));

        m_la = a, m_lb = b;
    }
}

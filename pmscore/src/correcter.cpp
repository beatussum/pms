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


#include "correcter.hpp"

#include "arduino/motoreductor.hpp"
#include "path/path_computer.hpp"
#include "path/position_computer.hpp"

void correcter::turn_left() const
{
    m_ma->set_power(0);
    m_mb->set_power(200);
}

void correcter::turn_right() const
{
    m_ma->set_power(200);
    m_mb->set_power(0);
}

void correcter::reset() const
{
    m_ma->set_power(200);
    m_mb->set_power(200);
}

void correcter::operator()()
{
    using namespace core;

    (*m_path_computer)(), (*m_position_computer)();

    auto walpha = atan2(
        m_path_computer->get_postion().m_y
        - m_position_computer->get_postion().m_y,
        m_path_computer->get_postion().m_x
        - m_position_computer->get_postion().m_x
    ) - (pi / 2);

    auto diff = angle_distance(m_position_computer->get_angle(), walpha);

    if (diff < -m_epsilon) {
        turn_right();
    } else if (diff > m_epsilon) {
        turn_left();
    } else {
        reset();
    }
}

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


#include "correcter.hpp"

#include "arduino/motoreductor.hpp"

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

void correcter::update_status(
    vector __rposition,
    vector __tposition,
    real __rangle
)
{
    real walpha = atan2(
        __tposition.y - __rposition.y,
        __tposition.x - __rposition.x
    ) - (PI / 2);

    real diff = angle_distance(__rangle, walpha);

    if (diff < -m_epsilon) {
        turn_right();
    } else if (diff > m_epsilon) {
        turn_left();
    } else {
        reset();
    }
}

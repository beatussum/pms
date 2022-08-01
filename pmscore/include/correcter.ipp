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


#include "arduino/motoreductor.hpp"

template <class _SpeedProfile>
void correcter<_SpeedProfile>::update_status(
    vector __rposition,
    vector __tposition,
    real __rangle
)
{
    switch (m_mode) {
        case mode::Fix:
            real gamma = HALF_PI - (__rposition - __tposition).angle();
            real diff  = angle_distance(gamma, __rangle);

            if (abs(diff) > m_epsilon) {
                m_mode = mode::Fix;

                m_speed_profile.init(__rangle, gamma);
            }

            break;
        case mode::Reset:
            m_mode      = mode::Fix;
            auto [a, b] = m_speed_profile.default_speed();

            m_motor_a->set_power(a);
            m_motor_b->set_power(b);

            break;
        case mode::Turn:
            if (m_speed_profile.is_ended()) {
                m_mode = mode::Reset;
            } else {
                auto [a, b] = m_speed_profile.compute_speed(__rangle);

                m_motor_a->set_power(a);
                m_motor_b->set_power(b);
            }

            break;
    }
}

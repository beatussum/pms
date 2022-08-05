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


namespace pmscore
{
    template <class _SpeedProfile, class _HeadingSpeedProfile>
    void correcter<_SpeedProfile, _HeadingSpeedProfile>::next_edge(
        real __x_0,
        real __x_f
    ) noexcept
    {
        m_speed_profile.init(__x_0, __x_f, 120);
    }

    template <class _SpeedProfile, class _HeadingSpeedProfile>
    void correcter<_SpeedProfile, _HeadingSpeedProfile>::update_status(
        real __distance,
        real __rangle,
        vector __rposition,
        vector __tposition
    )
    {
        int16_t k = 0;
        int16_t omega = m_speed_profile.compute_speed(__distance);

        if (omega != m_omega) {
            m_heading_mode = heading_mode::Off;
            m_omega        = omega;
        } else if (m_heading_mode == heading_mode::Off) {
            m_heading_mode = heading_mode::Fix;
        }

        switch (m_heading_mode) {
            case heading_mode::Fix:
                {
                    real gamma = (__tposition - __rposition).angle() - M_PI_2;

                    if (
                        m_heading_speed_profile.init(
                            __rangle,
                            gamma,
                            static_cast<uint8_t>(255 - m_omega)
                        )
                    )
                    {
                        m_heading_mode = heading_mode::Turn;
                    }
                }

                break;
            case heading_mode::Off:
                break;
            case heading_mode::Turn:
                {
                    k = m_heading_speed_profile.compute_speed(__rangle);

                    if (k == 0) {
                        m_heading_mode = heading_mode::Fix;
                    }
                }

                break;
        }

        m_motor_a->set_power(m_omega + k);
        m_motor_b->set_power(m_omega - k);
    }
}

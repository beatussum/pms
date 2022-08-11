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
    template <
        class _HeadingSpeedProfile,
        class _SoiSpeedProfile,
        class _SpeedProfile
    >
    constexpr void correcter<
        _HeadingSpeedProfile,
        _SoiSpeedProfile,
        _SpeedProfile
    >::next_edge(real __x_0, real __x_f) noexcept
    {
        m_heading_speed_mode = heading_speed_mode::Fix;
        m_soi_speed_mode     = soi_speed_mode::Run;
        m_speed_mode         = speed_mode::Off;

        m_speed_profile.init(__x_0, __x_f);
    }

    template <
        class _HeadingSpeedProfile,
        class _SoiSpeedProfile,
        class _SpeedProfile
    >
    void correcter<
        _HeadingSpeedProfile,
        _SoiSpeedProfile,
        _SpeedProfile
    >::update_status(
        real __distance,
        real __rangle,
        vector __rposition,
        vector __tposition
    )
    {
        int16_t k = 0;

        switch (m_speed_mode) {
            case speed_mode::Run:
                {
                    int16_t omega = -m_speed_profile.compute_speed(__distance);

                    if (omega != m_omega) {
                        if (omega < m_omega) {
                            m_heading_speed_mode = heading_speed_mode::Fix;
                        }

                        m_omega = omega;
                    }
                }

                break;
            case speed_mode::Off:
                m_omega = 0;

                break;
        }

        switch (m_heading_speed_mode) {
            case heading_speed_mode::Fix:
                {
                    real gamma = simplify_angle(
                        (__tposition - __rposition).angle() - M_PI_2
                    );

                    if (
                        (
                            (m_soi_speed_mode == soi_speed_mode::Off) &&
                            m_heading_speed_profile.init(
                                simplify_angle(__rangle),
                                gamma
                            )
                        ) ||
                        (
                            (m_soi_speed_mode == soi_speed_mode::Run) &&
                            m_soi_speed_profile.init(
                                simplify_angle(__rangle),
                                gamma
                            )
                        )
                    )
                    {
                        m_heading_speed_mode = heading_speed_mode::Turn;
                    } else {
                        m_soi_speed_mode = soi_speed_mode::Off;
                        m_speed_mode     = speed_mode::Run;
                    }
                }

                break;
            case heading_speed_mode::Off:
                break;
            case heading_speed_mode::Turn:
                {
                    switch (m_soi_speed_mode) {
                        case soi_speed_mode::Off:
                            k = m_heading_speed_profile.compute_speed(
                                simplify_angle(__rangle)
                            );

                            break;
                        case soi_speed_mode::Run:
                            k = m_soi_speed_profile.compute_speed(
                                simplify_angle(__rangle)
                            );

                            break;
                    }

                    if (k == 0) {
                        m_heading_speed_mode = heading_speed_mode::Fix;
                        m_soi_speed_mode     = soi_speed_mode::Off;
                        m_speed_mode         = speed_mode::Run;
                    }
                }

                break;
        }

        m_motor_a->set_power(m_omega + k);
        m_motor_b->set_power(m_omega - k);
    }
}

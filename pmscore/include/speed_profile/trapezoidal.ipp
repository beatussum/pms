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


namespace pmscore::speed_profile
{
    template <class _Distance>
    bool trapezoidal<_Distance>::init(
        real __x_0,
        real __x_f,
        uint8_t __M
    ) noexcept
    {
        real diff = m_distance(__x_0, __x_f);

        if (abs(diff) > m_epsilon) {
            m_is_increasing = (diff > 0);

            m_x_0 = __x_0;
            m_x_f = __x_f;

            if (m_is_increasing) {
                m_M = -static_cast<int16_t>(__M);

                m_x_1 = m_x_0 -
                    (static_cast<real>(m_m) + static_cast<real>(m_M)) / m_a;

                m_x_2 = m_x_f + static_cast<real>(m_M) / m_a;
            } else {
                m_M = static_cast<int16_t>(__M);

                m_x_1 = m_x_f + static_cast<real>(m_M) / m_a;

                m_x_2 = m_x_0 +
                    (static_cast<real>(m_m) - static_cast<real>(m_M)) / m_a;
            }

            if ((m_x_2 - m_x_1) < 0) {
                m_is_triangular = true;

                if (m_is_increasing) {
                    m_x_3 = (m_x_0 + m_x_f) / 2 + m_m / (2 * m_a);
                } else {
                    m_x_3 = (m_x_0 + m_x_f) / 2 - m_m / (2 * m_a);
                }
            } else {
                m_is_triangular = false;
            }

            return true;
        } else {
            return false;
        }
    }

    template <class _Distance>
    int16_t trapezoidal<_Distance>::compute_speed(real __x) noexcept
    {
        int16_t speed;

        if ((__x < m_x_0) == m_is_increasing) {
            speed = m_is_increasing ? -m_m : m_m;
        } else if ((__x > m_x_f) == m_is_increasing) {
            speed = 0;
        } else {
            if (
                ((__x < m_x_1) && m_is_triangular) ||
                ((__x < m_x_3) && !m_is_triangular)
            )
            {
                speed = static_cast<int16_t>(round(
                    m_is_increasing ?
                    m_a * (m_x_0 - __x) - m_m :
                    m_a * (__x - m_x_f)
                ));
            } else if (
                m_is_triangular ||
                ((__x > m_x_2) && !m_is_triangular)
            )
            {
                speed = static_cast<int16_t>(round(
                    m_is_increasing ?
                    m_a * (__x - m_x_f) :
                    m_a * (m_x_0 - __x) + m_m
                ));
            } else {
                speed = m_M;
            }
        }

        return speed;
    }
}

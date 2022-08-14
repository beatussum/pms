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
    constexpr bool trapezoidal<_Distance>::init(
        real __x_0,
        real __x_f
    ) noexcept
    {
        real diff = m_distance(__x_0, __x_f);

        if (abs(diff) > m_epsilon) {
            m_is_increasing = (diff > 0.);

            m_x_0 = __x_0;
            m_x_f = __x_f;

            if (m_is_increasing) {
                m_x_1 = m_x_0 +
                    (static_cast<real>(m_M) - static_cast<real>(m_m_0)) / m_a;

                m_x_2 = m_x_f +
                    (static_cast<real>(m_m_f) - static_cast<real>(m_M)) / m_a;
            } else {
                m_x_1 = m_x_f +
                    (static_cast<real>(m_M) - static_cast<real>(m_m_f)) / m_a;

                m_x_2 = m_x_0 +
                    (static_cast<real>(m_m_0) - static_cast<real>(m_M)) / m_a;
            }

            if (m_x_1 > m_x_2) {
                m_is_triangular = true;

                if (m_is_increasing) {
                    m_x_3 = (m_x_0 + m_x_f) / 2 +
                        (static_cast<real>(m_m_f) - static_cast<real>(m_m_0)) /
                        (2 * m_a);
                } else {
                    m_x_3 = (m_x_0 + m_x_f) / 2 +
                        (static_cast<real>(m_m_0) - static_cast<real>(m_m_f)) /
                        (2 * m_a);
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
    constexpr int16_t trapezoidal<_Distance>::compute_speed(real __x) noexcept
    {
        int16_t speed;

        if ((m_distance(__x, m_x_0) > 0.) == m_is_increasing) {
            speed = m_is_increasing ? -m_m_0 : m_m_0;
        } else if ((m_distance(__x, m_x_f) < 0.) == m_is_increasing) {
            speed = m_is_increasing ? -m_m_f : m_m_f;
        } else {
            if (
                (m_is_triangular && (m_distance(__x, m_x_1) > 0.)) ||
                (!m_is_triangular && (m_distance(__x, m_x_3) > 0.))
            )
            {
                speed = static_cast<int16_t>(round(
                    m_is_increasing ?
                    m_a * (m_x_0 - __x) - static_cast<real>(m_m_0) :
                    m_a * (__x - m_x_f) + static_cast<real>(m_m_f)
                ));
            } else if (
                m_is_triangular ||
                (!m_is_triangular && (m_distance(__x, m_x_2) < 0.))
            )
            {
                speed = static_cast<int16_t>(round(
                    m_is_increasing ?
                    m_a * (__x - m_x_f) - static_cast<real>(m_m_f) :
                    m_a * (m_x_0 - __x) + static_cast<real>(m_m_0)
                ));
            } else {
                speed = m_is_increasing ? -m_M : m_M;
            }
        }

        return speed;
    }

    template <class _Distance>
    constexpr typename trapezoidal<_Distance>::distance_type
    trapezoidal<_Distance>::get_distance() const noexcept_mov(distance_type)
    {
        return m_distance;
    }

    template <class _Distance>
    constexpr void trapezoidal<_Distance>::set_distance(
        distance_type __d
    ) noexcept_cm(distance_type)
    {
        m_distance = move(__d);
    }

    template <class _Distance>
    constexpr bool trapezoidal<_Distance>::is_increasing() const noexcept
    {
        return m_is_increasing;
    }

    template <class _Distance>
    constexpr bool trapezoidal<_Distance>::is_triangular() const noexcept
    {
        return m_is_triangular;
    }
}

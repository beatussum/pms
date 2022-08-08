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
    bool constant<_Distance>::init(real __x_0, real __x_f) noexcept
    {
        real diff = m_distance(__x_0, __x_f);

        if (abs(diff) > m_epsilon) {
            m_is_increasing = (diff > 0.);

            m_x_0 = __x_0;
            m_x_f = __x_f;

            return true;
        } else {
            return false;
        }
    }

    template <class _Distance>
    bool constant<_Distance>::init(
        real __x_0,
        real __x_f,
        uint8_t __M
    ) noexcept
    {
        return init(__x_0, __x_f);
    }

    template <class _Distance>
    int16_t constant<_Distance>::compute_speed(real __x) noexcept
    {
        if ((__x > m_x_f) == m_is_increasing) {
            return 0;
        } else {
            return m_is_increasing ?
                -static_cast<int16_t>(m_M) :
                static_cast<int16_t>(m_M);
        }
    }
}

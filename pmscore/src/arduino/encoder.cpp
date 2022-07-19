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


#include "arduino/encoder.hpp"

#include "arduino/motoreductor.hpp"

namespace arduino
{
    encoder::encoder(pin_t __pin)
        : m_pin(__pin)
        , m_inc(0.)
        , m_last(false)
        , m_reverse(false)
    {
        pinMode(m_pin, INPUT_PULLUP);
    }

    bool encoder::update_status()
    {
        if (digitalRead(m_pin) != m_last) {
            m_last = !m_last;

            if (m_reverse) {
                --m_inc;
            } else {
                ++m_inc;
            }

            return true;
        } else {
            return false;
        }
    }

    real encoder::angle() const noexcept
    {
        return m_inc * ((2 * PI) / m_knbinc);
    }
}

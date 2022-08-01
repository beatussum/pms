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


#ifndef PMSCORE_ARDUINO_ENCODER_HPP
#define PMSCORE_ARDUINO_ENCODER_HPP

#include "arduino/arduino.hpp"

namespace arduino
{
    class encoder
    {
    public:
        inline static constexpr real m_knbinc = 48.;
    public:
        encoder(pin_t __pin);
    public:
        bool update_status();
    public:
        real angle() const noexcept;
        real inc() const noexcept { return m_inc; }

        void reverse() noexcept { m_reverse = !m_reverse; }
    private:
        pin_t m_pin;

        real m_inc;
        bool m_last;
        bool m_reverse;
    };
}

#endif // PMSCORE_ARDUINO_ENCODER_HPP
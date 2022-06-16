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


#ifndef PMSCORE_ARDUINO_MOTOREDUCTOR_HPP
#define PMSCORE_ARDUINO_MOTOREDUCTOR_HPP

#include "arduino.hpp"

#include <Arduino.h>

namespace arduino
{
    class motoreductor
    {
    public:
        enum class direction : byte
        {
            Front,
            Back,
            Break,
            Off
        };
    public:
        motoreductor(
            pin_t __pina,
            pin_t __pinb,
            pin_t __pwm,
            direction __d = direction::Off,
            byte __valpwm = 0
        );
    public:
        direction get_direction() const noexcept { return m_direction; }
        void set_direction(direction);

        byte get_power() const noexcept { return m_valpwm; }
        void set_power(byte);
    public:
        void increase(int16_t = 1);
        void reduce(int16_t __p = 1) { increase(-__p); }
    private:
        pin_t m_pina, m_pinb;
        pin_t m_pwm;

        direction m_direction;
        byte m_valpwm;
    };
}

#endif // PMSCORE_ARDUINO_MOTOREDUCTOR_HPP

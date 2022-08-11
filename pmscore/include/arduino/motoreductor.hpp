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


#ifndef PMSCORE_ARDUINO_MOTOREDUCTOR_HPP
#define PMSCORE_ARDUINO_MOTOREDUCTOR_HPP

#include "arduino/arduino.hpp"

namespace pmscore::arduino
{
    class encoder;

    class motoreductor
    {
    public:
        enum class direction : uint8_t
        {
            Front,
            Back,
            Brake,
            Off
        };
    public:
        explicit motoreductor(
            pin_t __pin_a,
            pin_t __pin_b,
            pin_t __pin_pwm,
            encoder*,
            int16_t __power = 0
        );
    private:
        void __set_direction(direction);
    public:
        pin_t get_pin_a() const noexcept { return m_pin_a; }
        void set_pin_a(pin_t __p) noexcept { m_pin_a = __p; }

        pin_t get_pin_b() const noexcept { return m_pin_b; }
        void set_pin_b(pin_t __p) noexcept { m_pin_b = __p; }

        pin_t get_pin_pwm() const noexcept { return m_pin_pwm; }
        void set_pin_pwm(pin_t __p) noexcept { m_pin_pwm = __p; }

        encoder* get_encoder() const noexcept { return m_encoder; }
        void set_encoder(encoder* __e) noexcept { m_encoder = __e; }

        int16_t get_power() const noexcept { return m_power; }
        void set_power(int16_t);

        direction get_direction() const noexcept { return m_direction; }

        void increase_power(int16_t __p = 1) { set_power(m_power + __p); }
        void reduce_power(int16_t __p = 1) { increase_power(-__p); }
    public:
        void brake() { __set_direction(direction::Brake); }
        void disable() { __set_direction(direction::Off); }
    private:
        pin_t    m_pin_a;
        pin_t    m_pin_b;
        pin_t    m_pin_pwm;
        encoder* m_encoder;
        int16_t  m_power;

        direction m_direction;
    };
}

#endif // PMSCORE_ARDUINO_MOTOREDUCTOR_HPP

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

#include "arduino/encoder.hpp"

#include <Arduino.h>

namespace arduino
{
    motoreductor::motoreductor(
        pin_t __pina,
        pin_t __pinb,
        pin_t __pwm,
        encoder* __e,
        direction __d,
        uint8_t __power
    )
        : m_pin_a(__pina)
        , m_pin_b(__pinb)
        , m_pin_pwm(__pwm)
        , m_encoder(__e)
        , m_direction(__d)
        , m_power(__power)
    {
        pinMode(m_pin_a, OUTPUT);
        pinMode(m_pin_b, OUTPUT);
        pinMode(m_pin_pwm, OUTPUT);

        set_direction(m_direction);
        set_power(m_power);
    }

    void motoreductor::set_direction(direction __d)
    {
        if (__d != m_direction) {
            switch (m_direction = __d) {
                case direction::Front:
                    m_encoder->reverse();

                    digitalWrite(m_pin_a, HIGH);
                    digitalWrite(m_pin_b, LOW);

                    break;
                case direction::Back:
                    m_encoder->reverse();

                    digitalWrite(m_pin_a, LOW);
                    digitalWrite(m_pin_b, HIGH);

                    break;
                case direction::Break:
                    digitalWrite(m_pin_a, HIGH);
                    digitalWrite(m_pin_b, HIGH);

                    break;
                case direction::Off:
                    digitalWrite(m_pin_a, LOW);
                    digitalWrite(m_pin_b, LOW);

                    break;
            }
        }
    }

    void motoreductor::set_power(int16_t __b)
    {
        m_power = constrain(__b, -255, 255);

        if (m_power < 0) {
            set_direction(direction::Back);
            analogWrite(m_pin_pwm, -m_power);
        } else {
            set_direction(direction::Front);
            analogWrite(m_pin_pwm, m_power);
        }
    }
}

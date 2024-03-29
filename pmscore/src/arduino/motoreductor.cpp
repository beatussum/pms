/*
 * Copyright (C) 2022-2023 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
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

namespace pmscore::arduino
{
    motoreductor::motoreductor(
        pin_t __pin_a,
        pin_t __pin_b,
        pin_t __pin_pwm,
        encoder* __e,
        int16_t __power
    )
        : m_pin_a(__pin_a)
        , m_pin_b(__pin_b)
        , m_pin_pwm(__pin_pwm)
        , m_encoder(__e)
    {
        pinMode(m_pin_a, OUTPUT);
        pinMode(m_pin_b, OUTPUT);
        pinMode(m_pin_pwm, OUTPUT);

        set_power(__power);
    }

    void motoreductor::__set_direction(direction __d) const
    {
        direction current = get_direction();

        if (__d != current) {
            switch (__d) {
                case direction::Front:
                    digitalWrite(m_pin_a, HIGH);
                    digitalWrite(m_pin_b, LOW);

                    if (current == direction::Back) {
                        m_encoder->reverse();
                    }

                    break;
                case direction::Back:
                    digitalWrite(m_pin_a, LOW);
                    digitalWrite(m_pin_b, HIGH);

                    if (current == direction::Front) {
                        m_encoder->reverse();
                    }

                    break;
                case direction::Brake:
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

    motoreductor::direction motoreductor::get_direction() const
    {
        bool pin_status_a = (digitalRead(m_pin_a) == HIGH);
        bool pin_status_b = (digitalRead(m_pin_b) == HIGH);

        if (pin_status_a) {
            if (pin_status_b) {
                return direction::Brake;
            } else {
                return direction::Front;
            }
        } else if (pin_status_b) {
            return direction::Back;
        } else {
            return direction::Off;
        }
    }

    void motoreductor::set_power(int16_t __b) const
    {
        if (__b < 0) {
            __set_direction(direction::Back);
            analogWrite(m_pin_pwm, static_cast<int>(-__b));
        } else {
            __set_direction(direction::Front);
            analogWrite(m_pin_pwm, static_cast<int>(__b));
        }
    }
}

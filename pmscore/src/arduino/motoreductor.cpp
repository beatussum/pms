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


#include "arduino/motoreductor.hpp"

#include "arduino/encoder.hpp"

namespace arduino
{
    motoreductor::motoreductor(
        pin_t __pina,
        pin_t __pinb,
        pin_t __pwm,
        encoder* __e,
        direction __d,
        uint8_t __valpwm
    )
        : m_pina(__pina)
        , m_pinb(__pinb)
        , m_pwm(__pwm)
        , m_encoder(__e)
        , m_direction(__d)
        , m_valpwm(__valpwm)
    {
        pinMode(m_pina, OUTPUT);
        pinMode(m_pinb, OUTPUT);
        pinMode(m_pwm, OUTPUT);

        set_direction(m_direction);
        set_power(m_valpwm);
    }

    void motoreductor::set_direction(direction __d)
    {
        switch (__d) {
            case direction::Front:
                digitalWrite(m_pina, HIGH);
                digitalWrite(m_pinb, LOW);

                break;
            case direction::Back:
                digitalWrite(m_pina, LOW);
                digitalWrite(m_pinb, HIGH);

                break;
            case direction::Break:
                digitalWrite(m_pina, HIGH);
                digitalWrite(m_pinb, HIGH);

                break;
            case direction::Off:
                digitalWrite(m_pina, LOW);
                digitalWrite(m_pinb, LOW);

                break;
        }

        if (__d != m_direction) {
            switch (__d) {
                case direction::Front:
                case direction::Back:
                    m_encoder->reverse();

                    break;
            }
        }

        m_direction = __d;
    }

    void motoreductor::set_power(uint8_t __b)
    {
        analogWrite(m_pwm, m_valpwm = __b);
    }

    void motoreductor::increase_power(int16_t __p)
    {
        if (m_direction == direction::Back) {
            __p = m_valpwm - __p;
        } else {
            __p += m_valpwm;
        }

        if (__p < 0) {
            switch (m_direction) {
                case direction::Front:
                    set_direction(direction::Back);
                    set_power(-__p);

                    break;
                case direction::Back:
                    set_direction(direction::Front);
                    set_power(-__p);

                    break;
                default:
                    set_power(0);

                    break;
            }
        } else {
            set_power(min(__p, 255));
        }
    }
}

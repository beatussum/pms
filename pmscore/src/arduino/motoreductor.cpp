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


#include "motoreductor.hpp"

namespace arduino
{
    motoreductor::motoreductor(
        pin_t __pina,
        pin_t __pinb,
        pin_t __pwm,
        direction __d,
        byte __valpwm
    )
        : m_pina(__pina)
        , m_pinb(__pinb)
        , m_pwm(__pwm)
    {
        pinMode(m_pina, OUTPUT);
        pinMode(m_pinb, OUTPUT);
        pinMode(m_pwm, OUTPUT);

        set_direction(__d);
        set_power(__valpwm);
    }

    void motoreductor::set_direction(direction __d) const
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
    }

    void motoreductor::set_power(byte __b) const
    {
        analogWrite(m_pwm, __b);
    }
}

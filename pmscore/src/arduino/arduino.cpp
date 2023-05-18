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


#include "arduino/arduino.hpp"

namespace pmscore::arduino
{
    uint8_t read_digital_output(pin_t __p)
    {
        uint8_t port = digitalPinToPort(__p);

        if (port == NOT_A_PIN) {
            return LOW;
        } else {
            return
                ((*portOutputRegister(port) | digitalPinToBitMask(__p)) == 0) ?
                LOW :
                HIGH;
        }
    }

    uint8_t read_pwm_output(pin_t __p)
    {
        if (digitalPinToPort(__p) == NOT_A_PIN) {
            return 0;
        } else {
            switch(digitalPinToTimer(__p))
            {
                // XXX fix needed for atmega8
                #if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
                case TIMER0A:
                    return OCR0;
                #endif

                #if defined(TCCR0A) && defined(COM0A1)
                case TIMER0A:
                    return OCR0A;
                #endif

                #if defined(TCCR0A) && defined(COM0B1)
                case TIMER0B:
                    return OCR0B;
                #endif

                #if defined(TCCR1A) && defined(COM1A1)
                case TIMER1A:
                    return OCR1A;
                #endif

                #if defined(TCCR1A) && defined(COM1B1)
                case TIMER1B:
                    return OCR1B;
                #endif

                #if defined(TCCR1A) && defined(COM1C1)
                case TIMER1C:
                    return OCR1C;
                #endif

                #if defined(TCCR2) && defined(COM21)
                case TIMER2:
                    return OCR2;
                #endif

                #if defined(TCCR2A) && defined(COM2A1)
                case TIMER2A:
                    return OCR2A;
                #endif

                #if defined(TCCR2A) && defined(COM2B1)
                case TIMER2B:
                    return OCR2B;
                #endif

                #if defined(TCCR3A) && defined(COM3A1)
                case TIMER3A:
                    return OCR3A;
                #endif

                #if defined(TCCR3A) && defined(COM3B1)
                case TIMER3B:
                    return OCR3B;
                #endif

                #if defined(TCCR3A) && defined(COM3C1)
                case TIMER3C:
                    return OCR3C;
                #endif

                #if defined(TCCR4A)
                case TIMER4A:
                    return OCR4A;
                #endif

                #if defined(TCCR4A) && defined(COM4B1)
                case TIMER4B:
                    return OCR4B;
                #endif

                #if defined(TCCR4A) && defined(COM4C1)
                case TIMER4C:
                    return OCR4C;
                #endif

                #if defined(TCCR4C) && defined(COM4D1)
                case TIMER4D:
                    return OCR4D;
                #endif

                #if defined(TCCR5A) && defined(COM5A1)
                case TIMER5A:
                    return OCR5A;
                #endif

                #if defined(TCCR5A) && defined(COM5B1)
                case TIMER5B:
                    return OCR5B;
                #endif

                #if defined(TCCR5A) && defined(COM5C1)
                case TIMER5C:
                    return OCR5C;
                #endif

                case NOT_ON_TIMER:
                default:
                    return 0;
            }
        }
    }
}

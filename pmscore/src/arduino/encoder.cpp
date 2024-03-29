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


#include "arduino/encoder.hpp"

namespace pmscore::arduino
{
    encoder::encoder(pin_t __pin)
        : m_pin(__pin)
        , m_incrementation(0.)
        , m_reverse(false)
    {
        pinMode(m_pin, INPUT_PULLUP);
    }

    void set_main_encoders(encoder* __a, encoder* __b) noexcept
    {
        if (main_encoders[0] != nullptr) {
            detachInterrupt(digitalPinToInterrupt(main_encoders[0]->m_pin));
        }

        if (main_encoders[1] != nullptr) {
            detachInterrupt(digitalPinToInterrupt(main_encoders[1]->m_pin));
        }

        main_encoders[0] = __a;
        main_encoders[1] = __b;

        if (__a != nullptr) {
            attachInterrupt(
                digitalPinToInterrupt(__a->m_pin),
                update_main_encoder_status<0>,
                CHANGE
            );
        }

        if (__b != nullptr) {
            attachInterrupt(
                digitalPinToInterrupt(__b->m_pin),
                update_main_encoder_status<1>,
                CHANGE
            );
        }
    }
}

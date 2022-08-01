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


#include "arduino/encoders.hpp"

#include "position_computer.hpp"
#include "arduino/encoder.hpp"

namespace pmscore::arduino
{
    void encoders::update_status()
    {
        real last_angle_a = m_encoder_a->angle();
        real last_angle_b = m_encoder_b->angle();

        if (m_encoder_a->update_status() || m_encoder_b->update_status()) {
            m_computer->update_status(
                m_encoder_a->angle(),
                m_encoder_b->angle(),
                last_angle_a,
                last_angle_b
            );
        }
    }
}

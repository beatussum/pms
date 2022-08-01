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


#ifndef PMSCORE_ARDUINO_ENCODERS_HPP
#define PMSCORE_ARDUINO_ENCODERS_HPP

#include "math/math.hpp"

class position_computer;

namespace arduino
{
    class encoder;

    class encoders
    {
    public:
        explicit constexpr encoders(
            encoder* __encoder_a,
            encoder* __encoder_b,
            position_computer* __c
        ) noexcept
            : m_encoder_a(__encoder_a)
            , m_encoder_b(__encoder_b)
            , m_computer(__c)
        {}
    public:
        void update_status();
    private:
        encoder*           m_encoder_a;
        encoder*           m_encoder_b;
        position_computer* m_computer;
    };
}

#endif // PMSCORE_ARDUINO_ENCODERS_HPP

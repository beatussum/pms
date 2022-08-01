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


#ifndef PMSCORE_ARDUINO_ARDUINO_HPP
#define PMSCORE_ARDUINO_ARDUINO_HPP

#include "math/math.hpp"

#include <stdint.h>

namespace arduino
{
    using pin_t = uint8_t;

    inline static constexpr real d = 7.2;
    inline static constexpr real r = 2.2;
}

#endif // PMSCORE_ARDUINO_ARDUINO_HPP

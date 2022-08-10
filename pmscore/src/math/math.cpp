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


#include "math/math.hpp"

namespace pmscore
{
    real angle_distance(real __a, real __b)
    {
        __a = simplify_angle(__b) - simplify_angle(__a);

        if (__a > M_PI) {
            __a -= M_2PI;
        } else if (__a < -M_PI) {
            __a += M_2PI;
        }

        return __a;
    }
}

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


#ifndef PMSCORE_POSITION_COMPUTERS_HPP
#define PMSCORE_POSITION_COMPUTERS_HPP

#include "math/math.hpp"

class correcter;

namespace position
{
    class real_computer;
    class theoretical_computer_base;

    class computers
    {
    public:
        constexpr computers(
            real_computer* __rc,
            theoretical_computer_base* __tc,
            correcter* __c
        ) noexcept
            : m_rcomputer(__rc)
            , m_tcomputer(__tc)
            , m_correcter(__c)
        {}
    public:
        void update_status(real __angle_a, real __angle_b);
    private:
        real_computer*             m_rcomputer;
        theoretical_computer_base* m_tcomputer;
        correcter*                 m_correcter;
    };
}

#endif // PMSCORE_POSITION_COMPUTERS_HPP

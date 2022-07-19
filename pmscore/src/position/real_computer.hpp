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


#ifndef PMSCORE_POSITION_REAL_COMPUTER_HPP
#define PMSCORE_POSITION_REAL_COMPUTER_HPP

#include "math/vector.hpp"

namespace position
{
    class real_computer
    {
    public:
        real_computer() noexcept
            : m_alpha(0.)
            , m_pos()
            , m_la(0.)
            , m_lb(0.)
        {}
    public:
        explicit operator String() const { return static_cast<String>(m_pos); }
    public:
        void update_status(real __angle_a, real __angle_b);
    public:
        vector get_postion() const noexcept { return m_pos; }
        real get_angle() const noexcept { return m_alpha; }
    private:
        real   m_alpha;
        vector m_pos;
        real   m_la, m_lb;
    };
}

#endif // PMSCORE_POSITION_REAL_COMPUTER_HPP

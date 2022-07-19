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


#include "position/computers.hpp"

#include "correcter.hpp"
#include "position/real_computer.hpp"
#include "position/theoretical_computer.hpp"

namespace position
{
    void computers::update_status(real __angle_a, real __angle_b)
    {
        m_rcomputer->update_status(__angle_a, __angle_b);
        m_tcomputer->update_status(__angle_a, __angle_b);

        m_correcter->update_status(
            m_rcomputer->get_postion(),
            m_tcomputer->get_postion(),
            m_rcomputer->get_angle()
        );
    }
}

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


#ifndef PMSCORE_PATH_POSITION_COMPUTER_HPP
#define PMSCORE_PATH_POSITION_COMPUTER_HPP

#include "../math/vector.hpp"

#include <Arduino.h>

using namespace math;

namespace arduino
{
    class encoder;
}

namespace path
{
    class position_computer
    {
    public:
        position_computer(
            arduino::encoder* __a,
            arduino::encoder* __b
        ) noexcept
            : m_enca(__a)
            , m_encb(__b)
            , m_pos()
            , m_la(0.)
            , m_lb(0.)
        {}
    public:
        explicit operator String() const { return static_cast<String>(m_pos); }

        void operator()();
    public:
        vector get_postion() const noexcept { return m_pos; }
    private:
        arduino::encoder  *m_enca, *m_encb;
        math::vector      m_pos;
        real              m_la, m_lb;
    };
}

#endif // PMSCORE_PATH_POSITION_COMPUTER_HPP

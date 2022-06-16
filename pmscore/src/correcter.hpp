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


#ifndef PMSCORE_CORRECTER_HPP
#define PMSCORE_CORRECTER_HPP

#include "math/math.hpp"

using namespace math;

namespace arduino
{
    class motoreductor;
}

namespace path
{
    class path_computer_base;
    class position_computer;
}

class correcter
{
public:
    correcter(
        path::path_computer_base* __pac,
        path::position_computer* __poc,
        arduino::motoreductor* __ma,
        arduino::motoreductor* __mb,
        real __epsilon
    )
        : m_path_computer(__pac)
        , m_position_computer(__poc)
        , m_ma(__ma)
        , m_mb(__mb)
        , m_epsilon(__epsilon)
    {}
public:
    void turn_left() const;
    void turn_right() const;
    void reset() const;
public:
    void operator()();
private:
    path::path_computer_base* m_path_computer;
    path::position_computer*  m_position_computer;
    arduino::motoreductor *m_ma, *m_mb;
    real m_epsilon;
};

#endif // PMSCORE_CORRECTER_HPP

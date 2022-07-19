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


#ifndef PMSCORE_CORRECTER_HPP
#define PMSCORE_CORRECTER_HPP

#include "math/vector.hpp"

namespace arduino
{
    class motoreductor;
}

class correcter
{
public:
    correcter(
        arduino::motoreductor* __ma,
        arduino::motoreductor* __mb,
        real __epsilon
    )
        : m_ma(__ma)
        , m_mb(__mb)
        , m_epsilon(__epsilon)
    {}
public:
    void update_status(vector __rposition, vector __tposition, real __rangle);
public:
    void turn_left() const;
    void turn_right() const;
    void reset() const;
private:
    arduino::motoreductor *m_ma, *m_mb;
    real                  m_epsilon;
};

#endif // PMSCORE_CORRECTER_HPP

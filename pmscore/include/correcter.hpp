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

class correcter_base
{
public:
    virtual void update_status(
        vector __rposition,
        vector __tposition,
        real __rangle
    ) = 0;
};

template <class _SpeedProfile>
class correcter : public correcter_base
{
public:
    enum class mode
    {
        Fix,
        Reset,
        Turn
    };

    using speed_profile_type = _SpeedProfile;
public:
    /* TODO: perfect forwarding */
    explicit constexpr correcter(
        arduino::motoreductor* __motor_a,
        arduino::motoreductor* __motor_b,
        real __epsilon,
        _SpeedProfile __s
    ) noexcept
        : m_motor_a(__motor_a)
        , m_motor_b(__motor_b)
        , m_epsilon(__epsilon)
        , m_speed_profile(__s)
        , m_mode(mode::Fix)
    {}
public:
    void update_status(
        vector __rposition,
        vector __tposition,
        real __rangle
    ) override;
private:
    arduino::motoreductor* m_motor_a;
    arduino::motoreductor* m_motor_b;
    real                   m_epsilon;
    speed_profile_type     m_speed_profile;

    mode m_mode;
};

#include "correcter.ipp"

#endif // PMSCORE_CORRECTER_HPP

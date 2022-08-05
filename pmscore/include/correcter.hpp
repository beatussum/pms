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

#include "arduino/motoreductor.hpp"
#include "core/utility.hpp"
#include "math/vector.hpp"

namespace pmscore
{
    class correcter_base
    {
    public:
        virtual void next_edge(real __x_0, real __x_f) noexcept = 0;

        virtual void update_status(
            real __distance,
            real __rangle,
            vector __rposition,
            vector __tposition
        ) = 0;
    };

    template <class _SpeedProfile, class _HeadingSpeedProfile>
    class correcter : public correcter_base
    {
    public:
        enum class heading_mode
        {
            Fix,
            Off,
            Turn
        };

        using heading_speed_profile_type = _HeadingSpeedProfile;
        using speed_profile_type         = _SpeedProfile;
    public:
        explicit constexpr correcter(
            arduino::motoreductor* __motor_a,
            arduino::motoreductor* __motor_b,
            _SpeedProfile&& __s,
            _HeadingSpeedProfile&& __hs
        ) noexcept
            : m_motor_a(__motor_a)
            , m_motor_b(__motor_b)
            , m_heading_speed_profile(forward<_HeadingSpeedProfile>(__hs))
            , m_speed_profile(forward<_SpeedProfile>(__s))
            , m_heading_mode(heading_mode::Fix)
            , m_omega(0)
        {}
    public:
        void next_edge(real __x_0, real __x_f) noexcept override;

        void update_status(
            real __distance,
            real __rangle,
            vector __rposition,
            vector __tposition
        ) override;
    private:
        arduino::motoreductor*     m_motor_a;
        arduino::motoreductor*     m_motor_b;
        heading_speed_profile_type m_heading_speed_profile;
        speed_profile_type         m_speed_profile;

        heading_mode m_heading_mode;
        int16_t      m_omega;
    };
}

#include "correcter.ipp"

#endif // PMSCORE_CORRECTER_HPP

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

    template <
        class _HeadingSpeedProfile,
        class _SoiSpeedProfile,
        class _SpeedProfile
    >
    class correcter : public correcter_base
    {
    public:
        enum class heading_speed_mode : uint8_t
        {
            Fix,
            Off,
            Turn
        };

        enum class soi_speed_mode : uint8_t
        {
            Run,
            Off
        };

        enum class speed_mode : uint8_t
        {
            Run,
            Off
        };

        using heading_speed_profile_type = _HeadingSpeedProfile;
        using soi_speed_profile_type     = _SoiSpeedProfile;
        using speed_profile_type         = _SpeedProfile;
    public:
        explicit constexpr correcter(
            arduino::motoreductor* __motor_a,
            arduino::motoreductor* __motor_b,
            _HeadingSpeedProfile&& __hs = _HeadingSpeedProfile(),
            _SoiSpeedProfile&& __ss = _SoiSpeedProfile(),
            _SpeedProfile&& __s = _SpeedProfile()
        )
            : m_motor_a(__motor_a)
            , m_motor_b(__motor_b)
            , m_heading_speed_profile(forward<_HeadingSpeedProfile>(__hs))
            , m_soi_speed_profile(forward<_SoiSpeedProfile>(__ss))
            , m_speed_profile(forward<_SpeedProfile>(__s))
            , m_heading_speed_mode(heading_speed_mode::Fix)
            , m_soi_speed_mode(soi_speed_mode::Off)
            , m_speed_mode(speed_mode::Run)
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
        soi_speed_profile_type     m_soi_speed_profile;
        speed_profile_type         m_speed_profile;

        heading_speed_mode m_heading_speed_mode;
        soi_speed_mode     m_soi_speed_mode;
        speed_mode         m_speed_mode;
        int16_t            m_omega;
    };
}

#include "correcter.ipp"

#endif // PMSCORE_CORRECTER_HPP

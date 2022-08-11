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
#include "core/macros.hpp"
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
            _HeadingSpeedProfile&& __hs,
            _SoiSpeedProfile&& __ss,
            _SpeedProfile&& __s
        ) noexcept_pf(_HeadingSpeedProfile, _SoiSpeedProfile, _SpeedProfile)
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
        constexpr void next_edge(real __x_0, real __x_f) noexcept override;

        void update_status(
            real __distance,
            real __rangle,
            vector __rposition,
            vector __tposition
        ) override;
    public:
        arduino::motoreductor* get_motor_a() const noexcept
            { return m_motor_a; }

        void set_motor_a(arduino::motoreductor* __m) noexcept
            { m_motor_a = __m; }

        arduino::motoreductor* get_motor_b() const noexcept
            { return m_motor_b; }

        void set_motor_b(arduino::motoreductor* __m) noexcept
            { m_motor_b = __m; }

        heading_speed_profile_type get_heading_speed_profile()
        const noexcept_mov(heading_speed_profile_type)
            { return m_heading_speed_profile; }

        void set_heading_speed_profile(heading_speed_profile_type __hs)
        noexcept_cm(heading_speed_profile_type)
            { m_heading_speed_profile = move(__hs); }

        soi_speed_profile_type get_soi_speed_profile()
        const noexcept_mov(soi_speed_profile_type)
            { return m_soi_speed_profile; }

        void set_soi_speed_profile(soi_speed_profile_type __ss)
        noexcept_cm(soi_speed_profile_type)
            { m_soi_speed_profile = move(__ss); }

        speed_profile_type get_speed_profile()
        const noexcept_mov(speed_profile_type)
            { return m_speed_profile; }

        void set_speed_profile(speed_profile_type __s)
        noexcept_cm(speed_profile_type)
            { m_speed_profile = move(__s); }

        heading_speed_mode get_heading_speed_mode() const noexcept
            { return m_heading_speed_mode; }

        soi_speed_mode get_soi_speed_mode() const noexcept
            { return m_soi_speed_mode; }

        speed_mode get_speed_mode() const noexcept { return m_speed_mode; }
        int16_t get_omega() const noexcept { return m_omega; }
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

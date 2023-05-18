/*
 * Copyright (C) 2022-2023 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
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

/**
 * @file
 *
 * @brief Ce fichier implémente un correcteur de position.
 */

namespace pmscore
{
    /**
     * @brief Cette classe permet la correction de la position du robot.
     *
     * @tparam _HeadingSpeedProfile Type du profil de vitesse utilisé lors d'un
     * changement de cap.
     *
     * @tparam _SoiSpeedProfile Type du profil de vitesse utilisé lors d'un
     * changement de sommet.
     *
     * @tparam _SpeedProfile Type du profil de vitesse utilisé lors du parcours
     * du robot d'un sommet à un autre.
     */

    template <
        class _HeadingSpeedProfile,
        class _SoiSpeedProfile,
        class _SpeedProfile
    >
    class correcter
    {
    public:
        /**
         * @brief Mode du correcteur de vitesse angulaire (lors d'un changement
         * de cap).
         */

        enum class heading_speed_mode : uint8_t
        {
            Fix, ///< Correction activé.
            Off, ///< Correction désactivé.
            Turn ///< En cours de correction.
        };

        /**
         * @brief Mode du correcteur de vitesse angulaire (lors d'un changement
         * de sommet).
         */

        enum class soi_speed_mode : uint8_t
        {
            Run, ///< Correction en cours.
            Off  ///< Correction désactivé.
        };

        /**
         * @brief Mode du correcteur de vitesse angulaire (du parcours du robot
         * d'un sommet à un autre).
         */

        enum class speed_mode : uint8_t
        {
            Run, ///< Correction en cours.
            Off  ///< Correction désactivé.
        };

        /**
         * @brief Type du profil de vitesse utilisé lors d'un changement de
         * cap.
         */

        using heading_speed_profile_type = _HeadingSpeedProfile;

        /**
         * @brief Type du profil de vitesse utilisé lors d'un changement de
         * sommet.
         */

        using soi_speed_profile_type = _SoiSpeedProfile;

        /**
         * @brief Type du profil de vitesse utilisé lors du parcours du robot
         * d'un sommet à un autre.
         */

        using speed_profile_type = _SpeedProfile;
    public:
        /**
         * @brief Construit un objet `correcter`.
         *
         * @param __motor_a Motoréducteur A (celui de gauche).
         * @param __motor_b Motoréducteur B (celui de droite).
         * @param __hs Profil de vitesse utilisé lors d'un changement de cap.
         *
         * @param __ss Profil de vitesse utilisé lors d'un changement de
         * sommet.
         *
         * @param __s Profil de vitesse utilisé lors du parcours du robot d'un
         * sommet à un autre.
         *
         * @param __obstacle_distance_min Distance minimale à laquelle le robot
         * doit se situer par rapport à l'obstacle devant lui. En-dessous de
         * cette valeur, le robot s'arrête.
         */

        explicit constexpr correcter(
            arduino::motoreductor* __motor_a,
            arduino::motoreductor* __motor_b,
            _HeadingSpeedProfile __hs,
            _SoiSpeedProfile __ss,
            _SpeedProfile __s,
            real __obstacle_distance_min
        ) noexcept_cm(_HeadingSpeedProfile, _SoiSpeedProfile, _SpeedProfile)
            : m_motor_a(__motor_a)
            , m_motor_b(__motor_b)
            , m_heading_speed_profile(move(__hs))
            , m_soi_speed_profile(move(__ss))
            , m_speed_profile(move(__s))
            , m_obstacle_distance_min(__obstacle_distance_min)
            , m_heading_speed_mode(heading_speed_mode::Fix)
            , m_soi_speed_mode(soi_speed_mode::Off)
            , m_speed_mode(speed_mode::Run)
            , m_omega(0)
        {}
    public:
        /**
         * @brief Méthode appelée par le correcteur lors du changement de
         * sommet.
         *
         * @param __x_0 Distance de départ par rapport au sommet suivant.
         * @param __x_f Distance d'arrivée par rapport au sommet suivant.
         */

        constexpr void next_edge(real __x_0, real __x_f) noexcept;

        /**
         * @brief Actualise le statut du `correcter`.
         *
         * @param __distance La distance par rapport au sommet suivant.
         * @param __rangle Le cap suivi par le robot.
         * @param __rposition La position réelle du robot.
         * @param __tposition La position théorique du robot.
         *
         * @param __obstacle_distance La distance par rapport à l'obstacle se
         * situant devant le robot.
         */

        void update_status(
            real __distance,
            real __rangle,
            vector __rposition,
            vector __tposition,
            real __obstacle_distance
        );
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
    public:
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
        real                       m_obstacle_distance_min;

        heading_speed_mode m_heading_speed_mode;
        soi_speed_mode     m_soi_speed_mode;
        speed_mode         m_speed_mode;
        int16_t            m_omega;
    };
}

#include "correcter.ipp"

#endif // PMSCORE_CORRECTER_HPP

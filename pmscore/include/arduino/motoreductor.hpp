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


#ifndef PMSCORE_ARDUINO_MOTOREDUCTOR_HPP
#define PMSCORE_ARDUINO_MOTOREDUCTOR_HPP

#include "arduino/arduino.hpp"

/**
 * @file
 *
 * @brief Ce fichier implémente une interface logiciel-machine avec un
 * motoréducteur.
 */

namespace pmscore::arduino
{
    class encoder;

    /**
     * @brief Cette classe permet le pilotage d'un motoréducteur.
     */

    class motoreductor
    {
    public:
        /**
         * @brief Différents modes de fonctionnement du motoréducteur.
         */

        enum class direction : uint8_t
        {
            Front, ///< en marche avant.
            Back,  ///< en marche arrière.

            /**
             * @brief en mode freinage (le motoréducteur ne tourne pas mais
             * exerce un couple résistant).
             */

            Brake,

            /**
             * @brief en mode désactivé (le motoréducteur ne tourne pas et
             * n'exerce pas un couple résistant).
             */

            Off
        };
    public:
        /**
         * @brief Construit un objet `motoreductor`.
         *
         * @param __pin_a Pin A.
         * @param __pin_b Pin B.
         * @param __pin_pwm Pin P.W.M..
         *
         * @param __e Pointeur vers l'encodeur qui monitore le moteur en
         * question.
         *
         * @param __power Le rapport cyclique du signal P.W.M. alimentant le
         * motoréducteur. Cette valeur varie entre -255 et 255. Si cette valeur
         * est négative, le moteur a pour _direction_ _Back_ ; sinon, le moteur
         * a pour _direction_ _Front_. Le rapport cyclique est en lui-même codé
         * sur 8 bits (soit une valeur variant entre 0 et 255). La valeur par
         * défaut est nulle.
         */

        explicit motoreductor(
            pin_t __pin_a,
            pin_t __pin_b,
            pin_t __pin_pwm,
            encoder* __e,
            int16_t __power = 0
        );
    private:
        void __set_direction(direction) const;
    public:
        pin_t get_pin_a() const noexcept { return m_pin_a; }
        void set_pin_a(pin_t __p) noexcept { m_pin_a = __p; }

        pin_t get_pin_b() const noexcept { return m_pin_b; }
        void set_pin_b(pin_t __p) noexcept { m_pin_b = __p; }

        pin_t get_pin_pwm() const noexcept { return m_pin_pwm; }
        void set_pin_pwm(pin_t __p) noexcept { m_pin_pwm = __p; }

        encoder* get_encoder() const noexcept { return m_encoder; }
        void set_encoder(encoder* __e) noexcept { m_encoder = __e; }

        int16_t get_power() const noexcept
            { return read_pwm_output(m_pin_pwm); }

        void set_power(int16_t) const;

        direction get_direction() const;

        /**
         * @brief Augmente la puissance du motoréducteur.
         *
         * @param __p La valeur dont on augmente la puissance du motoréducteur.
         * Cette valeur peut être aussi bien positive que négative. De plus, si
         * celle-ci sort de l'intervalle de valeurs toléré (à savoir
         * \f$ [-255; 255] \f$), alors elle sature à la valeur extrême (basse
         * ou haute).
         */

        void increase_power(int16_t __p = 1) const
            { set_power(get_power() + __p); }

        /**
         * @brief Diminue la puissance du motoréducteur.
         *
         * @param __p La valeur dont on diminue la puissance du motoréducteur.
         *
         * @see increase_power
         */

        void reduce_power(int16_t __p = 1) const
            { increase_power(-__p); }
    public:
        /**
         * @brief Met la _direction_ du motoréducteur à _Brake_.
         */

        void brake() const { __set_direction(direction::Brake); }

        /**
         * @brief Met la _direction_ du motoréducteur à _Front_.
         */

        void enable() const { __set_direction(direction::Front); }

        /**
         * @brief Met la _direction_ du motoréducteur à _Off_.
         */

        void disable() const { __set_direction(direction::Off); }
    private:
        pin_t    m_pin_a;
        pin_t    m_pin_b;
        pin_t    m_pin_pwm;
        encoder* m_encoder;
    };
}

#endif // PMSCORE_ARDUINO_MOTOREDUCTOR_HPP

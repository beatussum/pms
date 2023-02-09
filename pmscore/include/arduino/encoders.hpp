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


#ifndef PMSCORE_ARDUINO_ENCODERS_HPP
#define PMSCORE_ARDUINO_ENCODERS_HPP

#include "arduino/encoder.hpp"
#include "math/math.hpp"

/**
 * @file
 *
 * @brief Ce fichier implémente une classe facilitant le pilotage entre deux
 * encodeurs.
 */

namespace pmscore
{
    class position_computer;
}

namespace pmscore::arduino
{
    /**
     * @brief Cette classe facilite le pilotage de deux encodeur.
     */

    class encoders
    {
        /**
         * @brief Spécifie deux `encoder`s en tant qu'encodeurs principaux.
         *
         * Afin qu'un `encoder` puisse correctement monitoré le moteur auquel
         * il est associé (afin que le membre `m_incrementation` est incrémenté
         * à chaque tour), il doit être défini en tant qu'encodeur principal.
         *
         * @param __e L'objet `encoders` regroupant les deux `encoder`s à spécifier
         * en tant qu'encodeurs principaux.
         */

        friend void set_main_encoders(const encoders& __e) noexcept;
    public:
        /**
         * @brief Construit un objet `encoders`.
         *
         * @param __encoder_a Pointeur pointant vers l'encodeur A soit celui
         *                    monitorant le moteur de la roue gauche.
         *
         * @param __encoder_b Pointeur pointant vers l'encodeur B soit celui
         *                    monitorant le moteur de la roue gauche.
         *
         * @param __c Pointeur vers un objet `position_computer`, un
         *            calculateur de position.
         */

        explicit constexpr encoders(
            encoder* __encoder_a,
            encoder* __encoder_b,
            position_computer* __c
        ) noexcept
            : m_encoder_a(__encoder_a)
            , m_encoder_b(__encoder_b)
            , m_computer(__c)
            , m_last_angle_a(0.)
            , m_last_angle_b(0.)
        {}
    public:
        /**
         * @brief Actualise le statut de l'objet.
         *
         * Actualise les valeurs des membres `m_encoder_a` et `m_encoder_b`,
         * puis actualise le calculateur de position.
         */

        void update_status();
    public:
        encoder* get_encoder_a() const noexcept { return m_encoder_a; }
        void set_encoder_a(encoder* __e) noexcept { m_encoder_a = __e; }

        encoder* get_encoder_b() const noexcept { return m_encoder_b; }
        void set_encoder_b(encoder* __e) noexcept { m_encoder_b = __e; }

        position_computer* get_computer() const noexcept { return m_computer; }
        void set_computer(position_computer* __c) noexcept;

        real get_last_angle_a() const noexcept { return m_last_angle_a; }
        real get_last_angle_b() const noexcept { return m_last_angle_a; }
    private:
        encoder*           m_encoder_a;
        encoder*           m_encoder_b;
        position_computer* m_computer;

        real m_last_angle_a;
        real m_last_angle_b;
    };

    /**
     * @brief Tableau contenant deux pointeurs pointant vers les deux encodeurs
     * principaux.
     *
     * Les deux encodeurs principaux sont les deux encodeurs dont la position
     * est effectivement monitorée par le programme. Cette implémentation
     * s'explique par les limitations imposées par les _« interrupt handler
     * functions »_.
     *
     * Le premier élément correspond à l'encodeur A (celui de gauche) et le
     * deuxième élément à l'encodeur B (celui de droite).
     *
     * @see avr/interrupt.h
     */

    inline encoder* main_encoders[] = {nullptr, nullptr};
}

#include "arduino/encoders.ipp"

#endif // PMSCORE_ARDUINO_ENCODERS_HPP

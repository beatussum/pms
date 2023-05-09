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


#ifndef PMSCORE_ARDUINO_CONNECTER_HPP
#define PMSCORE_ARDUINO_CONNECTER_HPP

#include "arduino/encoder.hpp"
#include "arduino/ultrasonic_sensor.hpp"
#include "timer.hpp"

/**
 * @file
 *
 * @brief Ce fichier implémente une classe facilitant la communication entre
 * les différents composants du robot.
 */

namespace pmscore
{
    class correcter_base;
    class position_computer;
}

namespace pmscore::arduino
{
    /**
     * @brief Cette classe facilite la communication entre les différents
     * composants du robot.
     */

    class connecter
    {
    public:
        /**
         * @brief Construit un objet `connecter`.
         *
         * @param __encoder_a Pointeur pointant vers l'encodeur A soit celui
         * monitorant le moteur de la roue gauche.
         *
         * @param __encoder_b Pointeur pointant vers l'encodeur B soit celui
         * monitorant le moteur de la roue gauche.
         *
         * @param __usensor Pointeur vers le capteur à ultraons permettant de
         * détecter la présence d'obstacle.
         *
         * @param __delay Période de l'envoie d'une impulsion ultrasonore et de
         * l'actualisation de la distance de l'obstacle.
         *
         * @param __c Pointeur vers un objet `position_computer`, un
         * calculateur de position.
         */

        explicit connecter(
            encoder* __encoder_a,
            encoder* __encoder_b,
            ultrasonic_sensor* __usensor,
            uint32_t __delay,
            position_computer* __computer,
            correcter_base* __correcter
        )
            : m_encoder_a(__encoder_a)
            , m_encoder_b(__encoder_b)
            , m_usensor(__usensor)
            , m_computer(__computer)
            , m_correcter(__correcter)
            , m_timer([&] { m_usensor->start_echoing(); }, __delay)
            , m_last_angle_a(0.)
            , m_last_angle_b(0.)
        {}
    public:
        void initialize();

        /**
         * @brief Actualise le statut de l'objet.
         *
         * Actualise les valeurs des membres `m_encoder_a` et `m_encoder_b`,
         * puis actualise le calculateur de position.
         */

        void update_status();
    public:
        encoder* get_encoder_a() const noexcept { return m_encoder_a; }
        encoder* get_encoder_b() const noexcept { return m_encoder_b; }
        ultrasonic_sensor* get_usensor() const noexcept { return m_usensor; }

        position_computer* get_computer() const noexcept { return m_computer; }

        void set_computer(position_computer* __c) noexcept
            { m_computer = __c; }

        real get_last_angle_a() const noexcept { return m_last_angle_a; }
        real get_last_angle_b() const noexcept { return m_last_angle_a; }
    private:
        encoder*           m_encoder_a;
        encoder*           m_encoder_b;
        ultrasonic_sensor* m_usensor;
        position_computer* m_computer;
        correcter_base*    m_correcter;

        timer m_timer;

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

    /**
     * @brief Spécifie deux `encoder` en tant qu'encodeurs principaux.
     *
     * Afin qu'un `encoder` puisse correctement monitoré le moteur auquel
     * il est associé (afin que le membre `m_incrementation` est incrémenté
     * à chaque tour), il doit être défini en tant qu'encodeur principal.
     *
     * @param __a L'encodeur A (associé à la roue gauche).
     * @param __b L'encodeur B (associé à la roue droite).
     */

    void set_main_encoders(encoder* __a, encoder* __b) noexcept;
}

#include "arduino/connecter.ipp"

#endif // PMSCORE_ARDUINO_CONNECTER_HPP

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


#ifndef PMSCORE_ARDUINO_ULTRASONIC_SENSOR_HPP
#define PMSCORE_ARDUINO_ULTRASONIC_SENSOR_HPP

#include "arduino/arduino.hpp"

/**
 * @file
 *
 * @brief Ce fichier implémente une interface logiciel-machine avec un
 * capteur à ultrason.
 */

namespace pmscore::arduino
{
    /**
     * @brief Cette classe permet le pilotage d'un capteur à ultrason.
     */

    class ultrasonic_sensor
    {
        friend void update_main_ultrasonic_sensor_status();
    public:
        /**
         * @brief Valeur approchée de la vitesse du son dans l'air.
         *
         * @note Cette variable est exprimée en centimère par microseconde.
         */

        static constexpr real speed_of_sound = 3.40e-2;
    public:
        /**
         * @brief Construit un objet `ultrasonic_sensor`.
         *
         * @param __pin_echo Pin Echo.
         * @param __pin_trig Pin Trig.
         */

        explicit ultrasonic_sensor(pin_t __pin_echo, pin_t __pin_trig);
    public:
        /**
         * @brief Initialise le processus d'actualisation de la distance de
         * l'obstacle se situant devant le capteur à ultrasons.
         *
         * Cette fonction commence par spécifier une valeur par défaut pour le
         * membre caractérisant la distance de l'obstacle se situant devant le
         * capteur à ultrason, puis l'émetteur envoie une rafale composée de 8
         * cycles ultrasoniques.
         *
         * Si le capteur à ultrason est spécifié en tant que principal, la
         * fonction `update_main_ultrasonic_sensor_status()` s'occupe
         * automatiquement de la détermination de la largeur de bande du signal
         * sur le pin Echo et en déduit la distance correspondante.
         */

        void start_echoing();

        /**
         * @brief Arrête le processus d'actualisation de la distance de
         * l'obstacle se situant devant le capteur à ultrasons.
         *
         * @see start_echoing()
         */

        void stop_echoing();
    public:
        pin_t get_pin_echo() const noexcept { return m_pin_echo; }
        void set_pin_echo(pin_t __p) { pinMode(m_pin_echo = __p, OUTPUT); }

        pin_t get_pin_trig() const noexcept { return m_pin_trig; }
        void set_pin_trig(pin_t __p) { pinMode(m_pin_trig = __p, OUTPUT); }
    public:
        real get_distance() const noexcept;

        uint32_t get_duration() const noexcept
            { return is_echoing() ? m_last_duration : m_duration; }

        bool is_echoing() const
            { return (read_digital_output(m_pin_echo) == HIGH); }
    private:
        pin_t m_pin_echo;
        pin_t m_pin_trig;

        volatile uint32_t m_duration;
        volatile uint32_t m_last_duration;
    };

    /**
     * @brief Tableau contenant un pointeur pointant vers le capteur à
     * ultrasons principal.
     *
     * Le capteur à ultrason principal est celui dont le statut est
     * effectivement monitoré par le programme. Cette implémentation s'explique
     * par les limitations imposées par les _« interrupt handler functions »_.
     *
     * @see avr/interrupt.h
     */

    inline ultrasonic_sensor* main_ultrasonic_sensor = nullptr;

    /**
     * @brief Spécifie un `ultrasonic_sensor` en tant que capteur à ultrasons
     * principal.
     *
     * Afin qu'un `ultrasonic_sensor` puisse correctement déterminer la
     * distance le séparant des obstacles devant lui, il doit être défini en
     * tant qu'encodeur principal.
     *
     * @param __us Le capteur à ultrasons à spécifié en tant que capteur à
     * ultrasons principal.
     */

    void set_main_ultrasonic_sensor(ultrasonic_sensor* __us);

    /**
     * @brief Actualise la distance de l'obstacle se situant devant le capteur
     * à ultrasons principal.
     *
     * @see main_ultrasonic_sensor
     */

    void update_main_ultrasonic_sensor_status();
}

#endif // PMSCORE_ARDUINO_ULTRASONIC_SENSOR_HPP

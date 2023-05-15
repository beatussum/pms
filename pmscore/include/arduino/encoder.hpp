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


#ifndef PMSCORE_ARDUINO_ENCODER_HPP
#define PMSCORE_ARDUINO_ENCODER_HPP

#include "arduino/arduino.hpp"

#include <stddef.h>

/**
 * @file
 *
 * @brief Ce fichier implémente une interface logiciel-machine avec un
 * encodeur.
 */

namespace pmscore::arduino
{
    /**
     * @brief Cette classe permet le pilotage d'un encodeur.
     */

    class encoder
    {
        friend void set_main_encoders(encoder* __a, encoder* __b) noexcept;

        template <size_t _n>
        friend void update_main_encoder_status() noexcept;
    public:
        /**
         * @brief Nombre d'incrémentations générées par tour.
         *
         * @see https://www.pololu.com/product/4845/
         */

        static constexpr real incrementation_counts = 1124.4288;
    public:
        /**
         * @brief Construit un objet `encoder`.
         *
         * @param __pin Pin de la carte Arduino sur lequel l'encodeur est
         * branché.
         */

        explicit encoder(pin_t __pin);
    public:
        pin_t get_pin() const noexcept { return m_pin; }

        real get_angle() const noexcept
            { return m_incrementation * (M_2PI / incrementation_counts); }

        real get_incrementation() const noexcept { return m_incrementation; }
        bool is_reverse() const noexcept { return m_reverse; }

        /**
         * @brief Active le mode de comptage inverse de l'encodeur.
         *
         * Lorsque le mode de comptage inverse est activé, le moteur monitoré
         * par l'encodeur est considéré comme tournant dans le sens négatif. En
         * d'autres termes, le membre `m_incrementation` est décrémenté (au
         * lieu d'être incrémenté) de 1.
         */

        void reverse() noexcept { m_reverse = !m_reverse; }
    private:
        pin_t m_pin;

        volatile real m_incrementation;
        bool          m_reverse;
    };

    /**
     * @brief Tableau contenant deux pointeurs pointant vers les deux encodeurs
     * principaux.
     *
     * Les deux encodeurs principaux sont ceux dont la position est
     * effectivement monitorée par le programme. Cette implémentation
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

    /**
     * @brief Actualise la position d'un des encodeurs principaux.
     *
     * @tparam _n Indice dans `main_encoders` de l'encodeur principal concerné.
     *
     * @see main_encoders
     */

    template <size_t _n>
    void update_main_encoder_status() noexcept;
}

#include "arduino/encoder.ipp"

#endif // PMSCORE_ARDUINO_ENCODER_HPP

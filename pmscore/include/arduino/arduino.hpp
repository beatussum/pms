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

#ifndef PMSCORE_ARDUINO_ARDUINO_HPP
#define PMSCORE_ARDUINO_ARDUINO_HPP

#include "math/math.hpp"

#include <Arduino.h>

#undef round

/**
 * @dir
 *
 * @brief Ce dossier implémente une interface logiciel-machine.
 */

/**
 * @file
 *
 * @brief Ce fichier implémente les éléménts communs et nécessaires au bon
 * fonctionnement des autres objets implémentés dans ce dossier.
 *
 * En particulier, ce fichier définie un certain nombre de constantes dont leur
 * correspondance physique est illustrée dans le schéma cinématique en annexe.
 */

/**
 * @brief Cet espace de nommage implémente une interface logiciel-machine.
 */

namespace pmscore::arduino
{
    /**
     * @brief Type utilisé pour décrire un pin de la carte Arduino.
     */

    using pin_t = uint8_t;

    /**
     * @brief Définition de \f$ d \f$.
     *
     * @note Cette variable est exprimée en centimètre.
     * @see Schéma cinématique en annexe.
     */

    constexpr real d = 8.20;

    /**
     * @brief Définition de \f$ r \f$.
     *
     * @note Cette variable est exprimée en centimètre.
     * @see Schéma cinématique en annexe.
     */

    constexpr real r = 2.55;

    constexpr real r_2  = (r / 2);       ///< Valeur de \f$ \frac{r}{2} \f$.
    constexpr real r_2d = (r / (2 * d)); ///< Valeur de \f$ \frac{r}{2d} \f$.

    /**
     * @brief Lit la valeur d'un pin numérique initialisé avec `analogWrite()`.
     *
     * @param __p Le pin numérique étudié.
     * @return La valeur sur un octet du pin numérique.
     *
     * @see https://github.com/arduino/ArduinoCore-avr/blob/1.8.6/cores/arduino/wiring_digital.c#L138-L163
     */

    uint8_t read_digital_output(pin_t __p);

    /**
     * @brief Lit la valeur d'un pin P.W.M. initialisé avec `analogWrite()`.
     *
     * @param __p Le pin P.W.M. étudié.
     * @return La valeur sur un octet du pin P.W.M..
     *
     * @see https://github.com/arduino/ArduinoCore-avr/blob/1.8.6/cores/arduino/wiring_analog.c#L92-L285
     */

    uint8_t read_pwm_output(pin_t __p);
}

#endif // PMSCORE_ARDUINO_ARDUINO_HPP

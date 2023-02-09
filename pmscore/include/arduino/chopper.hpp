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


#ifndef PMSCORE_ARDUINO_CHOPPER_HPP
#define PMSCORE_ARDUINO_CHOPPER_HPP

#include "arduino/arduino.hpp"

/**
 * @file
 *
 * @brief Ce fichier implémente une interface logiciel-machine avec un hacheur.
 */

namespace pmscore::arduino
{
    /**
     * @brief Cette classe permet le pilotage d'un hacheur.
     */

    class chopper
    {
    public:
        /**
         * @brief Construit un objet `chopper`.
         *
         * @param __pin_stby Pin de la carte Arduino sur lequel STBY est branché.
         */

        explicit chopper(pin_t __pin_stby);
    public:
        /**
         * @brief Active ou désactive le hacheur.
         *
         * @param __b Si cette variable vaut `true`, alors le hacheur est
         *            activé ; sinon, le hacheur est désactivé.
         */

        void enable(bool __b = true) const;

        /**
         * @brief Désactive le hacheur.
         */

        void disable() const { enable(false); }
    public:
        pin_t get_pin_stby() const noexcept { return m_pin_stby; }
    private:
        pin_t m_pin_stby;
    };
}

#endif // PMSCORE_ARDUINO_CHOPPER_HPP

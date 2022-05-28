/*
 * Copyright (C) 2022 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
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

#include "arduino.hpp"

namespace arduino
{
    class chopper
    {
    public:
        chopper(pin_t __stby);
    public:
        void enable(bool = true) const;
        void disable() const { enable(false); }
    private:
        pin_t m_stby;
    };
}

#endif // PMSCORE_ARDUINO_CHOPPER_HPP

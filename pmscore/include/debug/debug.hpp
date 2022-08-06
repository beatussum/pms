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


#ifndef PMSCORE_DEBUG_DEBUG_HPP
#define PMSCORE_DEBUG_DEBUG_HPP

#include <Arduino.h>

#define PMSCORE_DEBUG_MSG(__msg)                     \
    Serial.println(                                  \
        "\u001B[31m(\u001B[1;33mDEBUG\u001B[0;31m) " \
        "\u001B[0m(\u001B[0;32mmessage\u001B[0m) "   \
        __msg                                        \
    )

#define PMSCORE_DEBUG_VAR(__var)                     \
    Serial.println(                                  \
        "\u001B[31m(\u001B[1;33mDEBUG\u001B[0;31m) " \
        "\u001B[0m(\u001B[0;32mvariable\u001B[0m) "  \
        #__var                                       \
        " = " +                                      \
        static_cast<String>(__var)                   \
    )

#endif // PMSCORE_DEBUG_DEBUG_HPP

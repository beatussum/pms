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


#ifndef PMSCORE_CORE_CORE_HPP
#define PMSCORE_CORE_CORE_HPP

#include <Arduino.h>

/**
 * @dir
 *
 * @brief Ce dossier implémente des objets nécessaire au fonctionnement interne
 * du programme.
 *
 * @warning La plupart des objets implémentés ne doivent donc pas être utilisé
 * directement par l'utilisateur.
 */

/**
 * @file
 *
 * @brief Ce fichier implémente les éléménts communs et nécessaires au bon
 * fonctionnement des autres objets implémentés dans ce dossier.
 */

/**
 * @namespace pmscore::detail
 *
 * @brief Cet espace de nommage implémente des objets nécessaire au
 * fonctionnement interne du programme.
 *
 * @warning La plupart des objets implémentés ne doivent donc pas être utilisé
 * directement par l'utilisateur.
 */

/**
 * @brief Espace de nommage principal.
 */

namespace pmscore
{
    inline String operator ""_s(const char* __c, size_t)
        { return String(__c); }

    inline String operator ""_s(const char* __c) { return String(__c); }
    inline String operator ""_s(char __c) { return String(__c); }
}

#endif // PMSCORE_CORE_CORE_HPP

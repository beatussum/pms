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


#ifndef PMSCORE_MATH_MATH_HPP
#define PMSCORE_MATH_MATH_HPP

#include <math.h>

/**
 * @brief Valeur (approchée) de \f$ 2 \pi \f$.
 */

#define M_2PI 6.283185307179586476925286766559

/**
 * @dir
 *
 * @brief Ce dossier implémente des fonctions et objets mathématiques
 * élémentaires.
 */

/**
 * @file
 *
 * @brief Ce fichier implémente les éléménts communs et nécessaires au bon
 * fonctionnement des autres objets implémentés dans ce dossier.
 */

namespace pmscore
{
    /**
     * @brief Type réel utilisé.
     */

    using real = double;

    /**
     * @brief Calcule la distance minimale entre deux angles.
     *
     * @param __a Valeur de l'angle initial.
     * @param __b Valeur de l'angle final.
     *
     * @return La distance minimale entre deux angles. Cette valeur est
     * comprise entre \f$ -\pi \f$ et \f$ \pi \f$.
     */

    real angle_distance(real __a, real __b);

    /**
     * @brief Simplifie la valeur d'un angle.
     *
     * @param __a Angle à simplifier.
     *
     * @return Retourne la valeur de \p __a dans l'intervalle
     * \f$ [-\pi ; \pi] \f$.
     */
    inline real simplify_angle(real __a) { return fmod(__a, M_2PI); }
}

#endif // PMSCORE_MATH_MATH_HPP

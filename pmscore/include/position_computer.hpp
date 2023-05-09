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


#ifndef PMSCORE_POSITION_COMPUTER_HPP
#define PMSCORE_POSITION_COMPUTER_HPP

#include "core/iterator.hpp"
#include "math/vector.hpp"

/**
 * @file
 *
 * @brief Ce fichier implémente un calculateur de position.
 */

namespace pmscore
{
    /**
     * @brief Cette classe permet le calcul de la position du robot en fonction
     * de la position angulaire de l'axe des deux motoréducteurs.
     */

    class position_computer
    {
    public:
        /**
         * @brief Construit un objet `position_computer`.
         *
         * @tparam _n Nombre de vecteurs-arrêtes que comporte le chemin.
         * @param __c Pointeur vers le correcteur (de position).
         *
         * @param __tadvance Pourcentage de la norme du vecteur-arrête courant
         * qui est ajouté en avance à la position théorique sur la position
         * réelle.
         *
         * @param __tpath Chemin sous la forme de tableau de `_n`
         * vecteurs-arrêtes.
         *
         * @param __vertex_radius Rayon autour du prochain sommet à atteindre
         * où, s'il est dans cette zone, le robot passe au vecteur-arrête
         * suivant.
         */

        template <size_t _n>
        explicit position_computer(
            real __tadvance,
            const vector (&__tpath)[_n],
            real __vertex_radius
        );

        /**
         * @brief Détruit l'objet.
         *
         * Ce destructeur s'occupe de la libération de la mémoire occupé par le
         * chemin de vecteurs-arrêtes.
         */

        ~position_computer() { delete[] m_tpath; }
    public:
        explicit operator String() const;
    private:
        void __update_rstatus(
            real __angle_a,
            real __angle_b,
            real __last_angle_a,
            real __last_angle_b
        );

        void __update_tstatus(real __last_angle_a, real __last_angle_b);
    public:
        /**
         * @brief Actualise la position selon les paramètres donnés.
         *
         * @param __angle_a Position angulaire de l'axe du moteur A (le moteur
         * gauche).
         *
         * @param __angle_b Position angulaire de l'axe du moteur B (le moteur
         * droit).
         *
         * @param __last_angle_a Précédente position angulaire de l'axe du
         * moteur A (le moteur gauche).
         *
         * @param __last_angle_b Précédente position angulaire de l'axe du
         * moteur B (le moteur droit).
         */

        void update_status(
            real __angle_a,
            real __angle_b,
            real __last_angle_a,
            real __last_angle_b
        );
    public:
        real get_tadvance() const noexcept { return m_tadvance; }

        vector* get_path() const noexcept { return m_tpath; }

        template <size_t _n>
        void set_path(const vector (&)[_n]) noexcept;

        size_t get_path_size() const noexcept { return m_tpath_size; }
        real get_vertex_radius() const noexcept { return m_vertex_radius; }

        const vector* get_current_edge() const noexcept { return m_ti; }
        real get_current_edge_norm() const noexcept { return m_tcurrent_edge; }
        real get_distance() const noexcept { return m_distance; }
        real get_rangle() const noexcept { return m_rangle; }
        vector get_rpos() const noexcept { return m_rpos; }
        real get_tangle() const noexcept { return m_tangle; }
        vector get_tpos() const noexcept { return m_tpos + m_tcurrent_pos; }

        bool is_vertex_reached() const noexcept
            { return m_ris_vertex_reached; }
    private:
        real    m_tadvance;
        vector* m_tpath;
        real    m_vertex_radius;

        real          m_distance;
        real          m_rangle;
        bool          m_ris_vertex_reached;
        vector        m_rpos;
        real          m_tangle;
        real          m_tangle_a_0;
        real          m_tangle_b_0;
        real          m_tcurrent_edge;
        vector        m_tcurrent_pos;
        const vector* m_ti;
        vector        m_ti_unit;
        bool          m_tis_vertex_reached;
        size_t        m_tpath_size;
        vector        m_tpos;
        real          m_ttarget;
        vector        m_tvertex;
    };
}

#include "position_computer.ipp"

#endif // PMSCORE_POSITION_COMPUTER_HPP

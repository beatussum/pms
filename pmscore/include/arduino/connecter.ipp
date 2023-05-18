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


namespace pmscore::arduino
{
    template <class _Correcter>
    void connecter<_Correcter>::update_status()
    {
        real angle_a, angle_b, obstacle_distance;

        if (m_computer->is_vertex_reached()) {
            m_correcter.next_edge(
                m_computer->get_cdistance(),
                m_computer->get_current_edge_norm()
            );
        }

        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            angle_a           = m_encoder_a->get_angle();
            angle_b           = m_encoder_b->get_angle();
            obstacle_distance = m_usensor->get_distance();
        }

        m_timer.update_status();

        m_computer->update_status(
            angle_a,
            angle_b,
            m_last_angle_a,
            m_last_angle_b
        );

        m_last_angle_a = angle_a;
        m_last_angle_b = angle_b;

        m_correcter.update_status(
            m_computer->get_cdistance(),
            m_computer->get_cangle(),
            m_computer->get_cpos(),
            m_computer->get_tpos(),
            obstacle_distance
        );
    }
}

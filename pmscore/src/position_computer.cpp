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


#include "position_computer.hpp"

#include "arduino/arduino.hpp"
#include "correcter.hpp"

namespace pmscore
{
    position_computer::~position_computer()
    {
        delete[] m_tpath;
    }

    position_computer::operator String() const
    {
        return
            "real position: "_s + static_cast<String>(m_rpos) + " with " +
            m_rangle + " rad\n"_s +
            "theoretical position: "_s + static_cast<String>(get_tpos()) +
            " with " + m_tangle + " rad\n"_s;
    }

    void position_computer::__update_rstatus(
        real __angle_a,
        real __angle_b,
        real __last_angle_a,
        real __last_angle_b
    )
    {
        using namespace arduino;

        real v = (r / 2) *
            ((__angle_a - __last_angle_a) + (__angle_b - __last_angle_b));

        m_rangle  = (r / (2 * d)) * (__last_angle_b - __last_angle_a);
        m_rpos   += {-v * sin(m_rangle), v * cos(m_rangle)};
    }

    void position_computer::__update_tstatus(
        real __last_angle_a,
        real __last_angle_b
    )
    {
        using namespace arduino;

        if (m_tcurrent_edge == -1.) {
            if ((m_rpos - m_tvertex).norm() <= m_vertex_radius) {
                m_tcurrent_edge  = m_ti->norm();
                m_tvertex       += *m_ti;

                m_tpos += vector::with_polar_coordinates(
                    m_tadvance * m_tcurrent_edge, m_tangle
                );

                m_correcter->next_edge(m_rangle, m_tangle);
            }
        } else {
            real v         = (r / 2) * (__last_angle_a + __last_angle_b);
            m_tcurrent_pos = {v * cos(m_tangle), v * sin(m_tangle)};

            if (abs(v) >= (1 - m_tadvance) * m_tcurrent_edge) {
                if (++m_ti == (m_tpath + m_tpath_size)) {
                    m_ti = m_tpath;
                }

                m_tpos          += m_tcurrent_pos;
                m_tcurrent_pos   = {};
                m_tangle         = m_ti->angle();
                m_tcurrent_edge  = -1;
            }
        }
    }

    void position_computer::update_status(
        real __angle_a,
        real __angle_b,
        real __last_angle_a,
        real __last_angle_b
    )
    {
        __update_rstatus(__angle_a, __angle_b, __last_angle_a, __last_angle_b);
        __update_tstatus(__last_angle_a, __last_angle_b);

        m_correcter->update_status(m_rpos, get_tpos(), m_rangle);
    }
}

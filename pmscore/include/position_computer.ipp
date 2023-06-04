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


namespace pmscore
{
    template <size_t _n>
    position_computer::position_computer(
        correcter_base* __c,
        real __tadvance,
        const vector (&__tpath)[_n],
        real __vertex_radius,
        bool __is_looping
    )
        : m_correcter(__c)
        , m_is_looping(__is_looping)
        , m_tadvance(__tadvance)
        , m_tpath(new vector[_n])
        , m_vertex_radius(__vertex_radius)
        , m_rangle(0.)
        , m_distance(0.)
        , m_is_ended(false)
        , m_rpos()
        , m_tangle(__tpath[0].angle())
        , m_tangle_a_0(0.)
        , m_tangle_b_0(0.)
        , m_tcurrent_edge(__tpath[0].norm())
        , m_tcurrent_pos()
        , m_ti(m_tpath)
        , m_ti_unit(__tpath[0].unit())
        , m_tis_vertex_reached(false)
        , m_tpath_size(_n)

        , m_tpos(vector::with_polar_coordinates(
            m_tadvance * m_tcurrent_edge, m_tangle
        ))

        , m_ttarget((1 - m_tadvance) * m_tcurrent_edge)
        , m_tvertex()
    {
        copy(begin(__tpath), end(__tpath), m_tpath);

        m_correcter->next_edge(m_distance, m_tcurrent_edge);
    }

    template <size_t _n>
    void position_computer::set_path(const vector (&__p)[_n]) noexcept
    {
        if (m_tpath_size != _n) {
            delete[] m_tpath;

            m_tpath      = new vector[_n];
            m_tpath_size = _n;
        }

        copy(begin(__p), end(__p), m_tpath);
    }
}

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


template <size_t _n>
constexpr position_computer<_n>::position_computer(
    correcter_base* __c,
    real __tadvance,
    const vector (&__tpath)[_n],
    real __vertex_radius
) noexcept
    : m_correcter(__c)
    , m_tadvance(__tadvance)
    , m_tpath()
    , m_vertex_radius(__vertex_radius)
    , m_rangle(0.)
    , m_rpos()
    , m_tangle(__tpath[0].angle())
    , m_tcurrent_edge(__tpath[0].norm())
    , m_tcurrent_pos()
    , m_ti(begin(m_tpath))

    , m_tpos(vector::with_polar_coordinates(
        m_tadvance * m_tcurrent_edge, m_tangle
    ))

    , m_tvertex(__tpath[0])
{
    copy(begin(__tpath), end(__tpath), begin(m_tpath));
}

template <size_t _n>
position_computer<_n>::operator String() const
{
    return
        "real position: "_s + static_cast<String>(m_rpos) + '\n'_s +
        "theoretical position: "_s + static_cast<String>(m_tpos) + '\n'_s;
}

template <size_t _n>
void position_computer<_n>::__update_rstatus(
    real __angle_a,
    real __angle_b,
    real __last_angle_a,
    real __last_angle_b
)
{
    using namespace arduino;

    real v = (r / 2) *
        ((__angle_a - __last_angle_a) + (__angle_b - __last_angle_b));

    m_rangle  = (r / (2 * d)) * (__last_angle_a - __last_angle_b);
    m_rpos   += {-v * sin(m_rangle), v * cos(m_rangle)};
}

template <size_t _n>
void position_computer<_n>::__update_tstatus(
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

            /* TODO: spins on */
        }
    } else {
        real v         = (r / 2) * (__last_angle_a + __last_angle_b);
        m_tcurrent_pos = {v * cos(m_tangle), v * sin(m_tangle)};

        if (v >= m_tcurrent_edge) {
            if (++m_ti == end(m_tpath)) {
                m_ti = begin(m_tpath);
            }

            m_tpos          += m_tcurrent_pos;
            m_tcurrent_pos   = {};
            m_tangle         = m_ti->angle();
            m_tcurrent_edge  = -1;
        }
    }
}

template <size_t _n>
void position_computer<_n>::update_status(
    real __angle_a,
    real __angle_b,
    real __last_angle_a,
    real __last_angle_b
)
{
    __update_rstatus(__angle_a, __angle_b, __last_angle_a, __last_angle_b);
    __update_tstatus(__last_angle_a, __last_angle_b);

    m_correcter->update_status(m_rpos, m_tpos, m_rangle);
}

template <size_t _n>
constexpr correcter_base* position_computer<_n>::get_correcter() const noexcept
{
    return m_correcter;
}

template <size_t _n>
constexpr real position_computer<_n>::get_vertex_radius() const noexcept
{
    return m_vertex_radius;
}

template <size_t _n>
constexpr void position_computer<_n>::set_path(const path_type& __p) noexcept
{
    copy(begin(__p), end(__p), begin(m_tpath));
}

template <size_t _n>
constexpr const vector*
position_computer<_n>::get_current_edge() const noexcept
{
    return m_ti;
}

template <size_t _n>
constexpr vector position_computer<_n>::get_tpos() const noexcept
{
    return m_tpos + m_tcurrent_pos;
}

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


#include "position_computer.hpp"

#include "core/core.hpp"

#include "json/json_object.hpp"
#include "json/json_property.hpp"
#include "json/json_value.hpp"

#include "correcter.hpp"

namespace pmscore
{
    pmscore::json::json_object full_position_from(
        real __angle,
        const vector& __v
    )
    {
        return json::json_object({
            json::json_property("angle", json::json_value(__angle)),

            json::json_property(
                "position",
                static_cast<pmscore::json::json_object>(__v)
            ),
        });
    }

    position_computer::position_computer(
        real __tadvance,
        const vector* __tpath,
        size_t __tpath_size,
        real __vertex_radius,
        bool __loop
    )
        : m_loop(__loop)
        , m_tadvance(__tadvance)
        , m_tpath(new vector[__tpath_size])
        , m_tpath_size(__tpath_size)
        , m_vertex_radius(__vertex_radius)

        , m_cdistance(0.)
        , m_cangle(0.)
        , m_cis_vertex_reached(true)
        , m_cpos()

        , m_tangle(__tpath[0].angle())
        , m_tangle_a_0(0.)
        , m_tangle_b_0(0.)
        , m_tcurrent_edge_norm(__tpath[0].norm())
        , m_tcurrent_pos()
        , m_ti(m_tpath)
        , m_ti_unit(__tpath[0].unit())
        , m_tis_vertex_reached(false)

        , m_tpos(vector::with_polar_coordinates(
            m_tadvance * m_tcurrent_edge_norm, m_tangle
        ))

        , m_ttarget((1 - m_tadvance) * m_tcurrent_edge_norm)
        , m_tvertex()

        , m_is_ended(false)
    {
        copy(__tpath, __tpath + __tpath_size, m_tpath);
    }

    position_computer::operator pmscore::json::json_object() const
    {
        return pmscore::json::json_object({
            json::json_property(
                "computed",
                full_position_from(m_cangle, m_cpos)
            ),

            json::json_property(
                "target",
                full_position_from(m_tangle, get_tpos())
            ),

            json::json_property("timestamp", json::json_value(millis()))
        });
    }

    position_computer::operator String() const
    {
        return
            "real position: "_s + static_cast<String>(m_cpos) + " with "_s +
            m_cangle + " rad\n"_s +
            "theoretical position: "_s + static_cast<String>(get_tpos()) +
            " with "_s + m_tangle + " rad\n"_s;
    }

    void position_computer::__update_rstatus(
        real __angle_a,
        real __angle_b,
        real __last_angle_a,
        real __last_angle_b
    )
    {
        using namespace arduino;

        real v = r_2 *
            ((__angle_a - __last_angle_a) + (__angle_b - __last_angle_b));

        m_cangle  = r_2d * (__last_angle_b - __last_angle_a);
        m_cpos   += {-v * sin(m_cangle), v * cos(m_cangle)};
    }

    void position_computer::__update_tstatus(
        real __last_angle_a,
        real __last_angle_b
    )
    {
        using namespace arduino;

        m_cdistance = dot(m_cpos - m_tvertex, m_ti_unit);

        if (!m_tis_vertex_reached) {
            real v = r_2 * (
                (__last_angle_a - m_tangle_a_0) +
                (__last_angle_b - m_tangle_b_0)
            );

            m_tcurrent_pos = {v * cos(m_tangle), v * sin(m_tangle)};

            if (fabs(v) >= m_ttarget) {
                m_tis_vertex_reached = true;
            }
        } else if (
            fabs(m_cdistance - m_tcurrent_edge_norm) <= m_vertex_radius
        )
        {
            m_tvertex += *m_ti;

            if (++m_ti == (m_tpath + m_tpath_size)) {
                if (m_loop) {
                    m_ti = m_tpath;
                } else {
                    m_is_ended = true;
                }
            }

            m_ti_unit = m_ti->unit();

            m_cdistance           = dot(m_cpos - m_tvertex, m_ti_unit);
            m_cis_vertex_reached  = true;

            m_tangle              = m_ti->angle();
            m_tangle_a_0          = __last_angle_a;
            m_tangle_b_0          = __last_angle_b;
            m_tcurrent_edge_norm  = m_ti->norm();
            m_tis_vertex_reached  = false;
            m_tpos               += m_tcurrent_pos;
            m_ttarget             = (1 - m_tadvance) * m_tcurrent_edge_norm;

            m_tcurrent_pos = {};

            m_tpos += vector::with_polar_coordinates(
                m_tadvance * m_tcurrent_edge_norm, m_tangle
            );
        }
    }

    void position_computer::update_status(
        real __angle_a,
        real __angle_b,
        real __last_angle_a,
        real __last_angle_b
    )
    {
        if (m_cis_vertex_reached) {
            m_cis_vertex_reached = false;
        }

        __update_rstatus(__angle_a, __angle_b, __last_angle_a, __last_angle_b);
        __update_tstatus(__last_angle_a, __last_angle_b);
    }

    void position_computer::set_path(
        const vector* __tpath,
        size_t __tpath_size
    ) noexcept
    {
        if (m_tpath_size != __tpath_size) {
            delete[] m_tpath;

            m_tpath      = new vector[__tpath_size];
            m_tpath_size = __tpath_size;
        }

        copy(__tpath, __tpath + __tpath_size, m_tpath);
    }
}

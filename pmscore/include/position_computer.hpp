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


#ifndef PMSCORE_POSITION_COMPUTER_HPP
#define PMSCORE_POSITION_COMPUTER_HPP

#include "core/core.hpp"
#include "core/iterator.hpp"
#include "math/vector.hpp"

class correcter_base;

class position_computer
{
public:
    template <size_t _n>
    explicit position_computer(
        correcter_base*,
        real __tadvance,
        const vector (&__tpath)[_n],
        real __vertex_radius
    ) noexcept;

    ~position_computer();
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
    void update_status(
        real __angle_a,
        real __angle_b,
        real __last_angle_a,
        real __last_angle_b
    );
public:
    correcter_base* get_correcter() const noexcept { return m_correcter; }
    real get_tadvance() const noexcept { return m_tadvance; }

    const vector* get_path() const noexcept { return m_tpath; }
    vector* get_path() noexcept { return m_tpath; }

    template <size_t _n>
    void set_path(const vector (&)[_n]) noexcept;

    real get_vertex_radius() const noexcept { return m_vertex_radius; }

    real get_rangle() const noexcept { return m_rangle; }
    vector get_rpos() const noexcept { return m_rpos; }
    real get_tangle() const noexcept { return m_tangle; }
    const vector* get_current_edge() const noexcept { return m_ti; }
    size_t get_path_size() const noexcept { return m_tpath_size; }
    vector get_tpos() const noexcept { return m_tpos + m_tcurrent_pos; }
    vector get_tvertex() const noexcept { return m_tvertex; }
private:
    correcter_base* m_correcter;
    real            m_tadvance;
    vector*         m_tpath;
    real            m_vertex_radius;

    real          m_rangle;
    vector        m_rpos;
    real          m_tangle;
    real          m_tcurrent_edge;
    vector        m_tcurrent_pos;
    const vector* m_ti;
    size_t        m_tpath_size;
    vector        m_tpos;
    vector        m_tvertex;
};

#include "position_computer.ipp"

#endif // PMSCORE_POSITION_COMPUTER_HPP

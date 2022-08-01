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

#include "math/vector.hpp"

class correcter_base;

class position_computer_base
{
public:
    virtual void update_status(
        real __angle_a,
        real __angle_b,
        real __last_angle_a,
        real __last_angle_b
    ) = 0;
};

template <size_t _n>
class position_computer : public position_computer_base
{
public:
    inline static constexpr size_t path_size = _n;

    using path_type = vector[path_size];
public:
    explicit constexpr position_computer(
        correcter_base*,
        real __tadvance,
        const vector (&__tpath)[_n],
        real __vertex_radius
    ) noexcept;
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
    ) override;
public:
    constexpr correcter_base* get_correcter() const noexcept;
    constexpr real get_tadvance() const noexcept { return m_tadvance; }

    constexpr const path_type& get_path() const noexcept { return m_tpath; }
    constexpr path_type& get_path() noexcept { return m_tpath; }
    constexpr void set_path(const path_type&) noexcept;

    constexpr real get_vertex_radius() const noexcept;

    constexpr real get_rangle() const noexcept { return m_rangle; }
    constexpr vector get_rpos() const noexcept { return m_rpos; }
    constexpr real get_tangle() const noexcept { return m_tangle; }
    constexpr const vector* get_current_edge() const noexcept;
    constexpr vector get_tpos() const noexcept;
    constexpr vector get_tvertex() const noexcept { return m_tvertex; }
private:
    correcter_base* m_correcter;
    real            m_tadvance;
    path_type       m_tpath;
    real            m_vertex_radius;

    real          m_rangle;
    vector        m_rpos;
    real          m_tangle;
    real          m_tcurrent_edge;
    vector        m_tcurrent_pos;
    const vector* m_ti;
    vector        m_tpos;
    vector        m_tvertex;
};

#include "position_computer.ipp"

#endif // PMSCORE_POSITION_COMPUTER_HPP

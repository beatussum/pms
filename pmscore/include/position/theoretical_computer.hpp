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


#ifndef PMSCORE_POSITION_THEORETICAL_COMPUTER_HPP
#define PMSCORE_POSITION_THEORETICAL_COMPUTER_HPP

#include "math/vector.hpp"

namespace position
{
    class theoretical_computer_base
    {
    public:
        virtual void update_status(real __angle_a, real __angle_b) = 0;
    public:
        virtual vector get_postion() const noexcept = 0;
    };

    template <size_t _n>
    class theoretical_computer : public theoretical_computer_base
    {
    public:
        inline static constexpr auto m_ksize = _n;
    public:
        using path_type = vector[m_ksize];
    public:
        theoretical_computer(const vector (&__path)[_n]);
    public:
        explicit operator String() const { return static_cast<String>(m_pos); }
        void update_status(real __angle_a, real __angle_b) override;
    public:
        vector get_postion() const noexcept override { return m_pos; }
    public:
        path_type m_path;

        vector        m_pos;
        const vector* m_i;
        real          m_current_path;
        real          m_path_angle;
        real          m_la, m_lb;
    };
}

#include "position/theoretical_computer.ipp"

#endif // PMSCORE_POSITION_THEORETICAL_COMPUTER_HPP

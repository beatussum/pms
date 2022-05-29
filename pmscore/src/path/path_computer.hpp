/*
 * Copyright (C) 2022 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
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


#ifndef PMSCORE_PATH_PATH_COMPUTER_HPP
#define PMSCORE_PATH_PATH_COMPUTER_HPP

#include "../arduino/encoder.hpp"
#include "../core/core.hpp"
#include "../math/vector.hpp"

using namespace math;

namespace path
{
    template <size_t _n>
    class path_computer
    {
    public:
        inline static constexpr auto m_ksize = _n;

        using path_type = vector[m_ksize];
    public:
        path_computer(
            const vector (&__path)[_n],
            arduino::encoder* __a,
            arduino::encoder* __b
        )
            : m_enca(__a)
            , m_encb(__b)
            , m_pos()
            , m_i(&m_path[0])
            , m_current_path(__path[0].norm())
            , m_path_angle(__path[0].angle())
            , m_la(0.)
            , m_lb(0.)
        {
            using namespace core;

            copy(begin(__path), end(__path), begin(m_path));
        }
    public:
        explicit operator String() const { return static_cast<String>(m_pos); }

        void operator()()
        {
            using namespace core;
            using namespace arduino;

            (*m_enca)(), (*m_encb)();

            auto a = m_enca->angle(), b = m_encb->angle();

            auto v = (kr / 2) * ((a - m_la) + (b - m_lb));

            m_pos += vector(v * cos(m_path_angle), v * sin(m_path_angle));

            m_la = a, m_lb = b;

            if ((m_current_path -= v) <= 0) {
                if (++m_i == end(m_path)) {
                    m_i = begin(m_path);
                }

                m_current_path = m_i->norm();
                m_path_angle   = m_i->angle();
            }
        }
    public:
        vector get_postion() const noexcept { return m_pos; }
    private:
        arduino::encoder *m_enca, *m_encb;
        path_type        m_path;
        vector           m_pos;

        const vector* m_i;
        real          m_current_path;
        real          m_path_angle;
        real          m_la, m_lb;
    };
}

#endif // PMSCORE_PATH_PATH_COMPUTER_HPP

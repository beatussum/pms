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


#ifndef PMSCORE_TIMER_HPP
#define PMSCORE_TIMER_HPP

#include "core/macros.hpp"

namespace pmscore
{
    template <class _T>
    class timer
    {
    public:
        using callback_type = _T;
    public:
        constexpr timer() noexcept_def(_T)
            : m_delay(0)
            , m_callback()
            , m_time(0)
        {}

        explicit timer(unsigned long __delay, _T __callback)
            : m_delay(__delay)
            , m_callback(move(__callback))
            , m_time(0)
        {}
    public:
        unsigned long get_delay() const noexcept { return m_delay; }
        void set_delay(unsigned long __d) noexcept { m_delay = __d; }

        _T get_callback() const noexcept_mov(_T) { return m_callback; }
        void set_callback(_T __c) noexcept_mov(_T) { m_callback = move(__c); }
    public:
        void update_status() noexcept_if(declval<_T>()());
    private:
        unsigned long m_delay;
        callback_type m_callback;

        unsigned long m_time;
    };
}

#include "timer.ipp"

#endif // PMSCORE_TIMER_HPP

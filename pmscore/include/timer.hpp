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
#include "core/utility.hpp"

#include <stdint.h>

namespace pmscore
{
    class callback_base
    {
    public:
        virtual void operator()() = 0;
    };

    template <class _T>
    class callback final : public callback_base
    {
    public:
        using callback_type = _T;
    public:
        callback(_T&& __callback) noexcept_pf(_T)
            : m_callback(forward<_T>(__callback))
        {}
    public:
        void operator()() override { m_callback(); }
    private:
        callback_type m_callback;
    };

    class timer
    {
    public:
        constexpr timer()
            : m_delay(0)
            , m_callback(nullptr)
            , m_time(0)
        {}

        template <class _T>
        explicit timer(_T&& __callback, uint32_t __delay)
            : m_callback(new callback(forward<_T>(__callback)))
            , m_delay(__delay)
            , m_time(0)
        {}
    public:
        callback_base* get_callback() const noexcept { return m_callback; }

        template <class _T>
        void set_callback(_T&&);

        uint32_t get_delay() const noexcept { return m_delay; }
        void set_delay(uint32_t __d) noexcept { m_delay = __d; }
    public:
        void update_status();
    private:
        callback_base* m_callback;
        uint32_t       m_delay;

        uint32_t m_time;
    };
}

#include "timer.ipp"

#endif // PMSCORE_TIMER_HPP

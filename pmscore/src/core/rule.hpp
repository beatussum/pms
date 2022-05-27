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


#ifndef PMSCORE_CORE_RULE_HPP
#define PMSCORE_CORE_RULE_HPP

#include <Arduino.h>

namespace core
{
    class rule
    {
        template <size_t _N>
        friend class looper;
    public:
        using callable_type = void (*)();
        using time_type     = unsigned int;
    public:
        constexpr rule()
            : m_chrono(0)
            , m_step(0)
            , m_callable(nullptr)
        {}

        rule(time_type __step, callable_type __c)
            : m_chrono(0)
            , m_step(__step)
            , m_callable(__c)
        {}
    public:
        void actualize(time_type);
    private:
        time_type     m_chrono;
        time_type     m_step;
        callable_type m_callable;
    };
}

#endif // PMSCORE_CORE_RULE_HPP

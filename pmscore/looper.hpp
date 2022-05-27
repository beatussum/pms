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


#ifndef PMSCORE_LOOPER_HPP
#define PMSCORE_LOOPER_HPP

#include "core.hpp"
#include "rule.hpp"

namespace core
{
    template <size_t _N>
    class looper
    {
    public:
        static inline constexpr auto m_ksize = _N;

        using time_type  = unsigned long; 
        using rules_type = rule[m_ksize];
    public:
        looper(const rules_type& __rules)
        {
            copy(begin(__rules), end(__rules), begin(m_rules));
        }
    public:
        void init(bool __sort = true)
        {        
            if (__sort) {
                for (auto r = (begin(m_rules) + 1); r != end(m_rules); ++r) {
                    auto x = *r;
                    auto s = r;

                    for (; (s != begin(m_rules)) && (s[-1].m_step > x.m_step); --s) {
                        *s = s[-1];
                    }

                    *s = x;
                }
            }

            for (auto& r : m_rules) {
                r.m_chrono = millis();
            }            
        }

        void actualize(time_type __t = millis())
        {
            for (auto r = begin(m_rules); r != end(m_rules); ++r) {
                r->actualize(__t);
            }
        }
    private:
        rules_type m_rules;
    };
}

#endif // PMSCORE_LOOPER_HPP

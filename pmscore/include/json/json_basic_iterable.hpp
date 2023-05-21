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


#ifndef PMSCORE_JSON_JSON_BASIC_ITERABLE_HPP
#define PMSCORE_JSON_JSON_BASIC_ITERABLE_HPP

#include "json/json_variant.hpp"

namespace pmscore::json
{
    class json_basic_iterable : public json_variant
    {
    public:
        using reference_type       = json_variant&;
        using const_reference_type = const json_variant&;
        using size_type            = size_t;
    public:
        explicit json_basic_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator,
            size_type __n
        ) noexcept
            : json_variant(__type)
            , m_begin_separator(__begin_separator)
            , m_end_separator(__end_separator)
            , m_size(__n)
        {}
    public:
        virtual void push_back(const json_variant&) = 0;
    public:
        char get_begin_separator() const noexcept { return m_begin_separator; }
        char get_end_separator() const noexcept { return m_end_separator; }
        size_type size() const noexcept { return m_size; }
    private:
        char m_begin_separator;
        char m_end_separator;
    protected:
        size_type m_size;
    };
}

#endif // PMSCORE_JSON_JSON_BASIC_ITERABLE_HPP

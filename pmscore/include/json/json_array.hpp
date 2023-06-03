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


#ifndef PMSCORE_JSON_JSON_ARRAY_HPP
#define PMSCORE_JSON_JSON_ARRAY_HPP

#include "json/json_iterable.hpp"

namespace pmscore::json
{
    class json_array : public json_iterable
    {
    public:
        json_array()
            : json_iterable(json_type::Array, '[', ']')
        {}

        explicit json_array(size_t __n)
            : json_iterable(json_type::Array, '[', ']', __n)
        {}

        explicit json_array(const json_variant* __values, size_t __n)
            : json_iterable(json_type::Array, '[', ']', __values, __n)
        {}

        template <class _T, size_t _n>
        explicit json_array(const _T (&__values)[_n])
            : json_iterable(json_type::Array, '[', ']', __values)
        {}

        explicit json_array(const_iterator __begin, const_iterator __end)
            : json_iterable(json_type::Array, '[', ']', __begin, __end)
        {}

        explicit json_array(size_t __n, const json_variant& __value)
            : json_iterable(json_type::Array, '[', ']', __n, __value)
        {}

        json_variant* clone() const override { return new json_array(*this); }
    };
}

#endif // PMSCORE_JSON_json_array_HPP

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


#ifndef PMSCORE_JSON_JSON_OBJECT_HPP
#define PMSCORE_JSON_JSON_OBJECT_HPP

#include "json/json_iterable.hpp"

namespace pmscore::json
{
    class json_object : public json_iterable
    {
    public:
        json_object()
            : json_iterable(json_type::Object, '{', '}')
        {}

        explicit json_object(size_t __n)
            : json_iterable(json_type::Object, '{', '}', __n)
        {}

        explicit json_object(const json_variant* __values, size_t __n)
            : json_iterable(json_type::Object, '{', '}', __values, __n)
        {}

        template <class _T, size_t _n>
        explicit json_object(_T (&__values)[_n]);
            : json_iterable(json_type::Object, '{', '}', __values, _n)
        {}

        explicit json_object(const_iterator __begin, const_iterator __end)
            : json_iterable(json_type::Object, '{', '}', __begin, __end)
        {}

        explicit json_object(size_t __n, const json_variant& __value)
            : json_iterable(json_type::Object, '{', '}', __n, __value)
        {}

        json_variant* clone() const override { return new json_object(*this); }
    };
}

#endif // PMSCORE_JSON_JSON_OBJECT_HPP

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


#ifndef PMSCORE_JSON_JSON_VALUE_HPP
#define PMSCORE_JSON_JSON_VALUE_HPP

#include "core/utility.hpp"
#include "json/json.hpp"
#include "json/json_variant.hpp"

namespace pmscore::json
{
    class json_value : public json_variant
    {
    private:
        union underlying_type
        {
            ~underlying_type() = default;

            bool       as_bool;
            char       as_char;
            json_float as_float;
            json_int   as_int;
            nullptr_t  as_null;
            json_uint  as_uint;
            String     as_string;
        };
    public:
        template <class _T>
        json_value(_T __value)
            : json_variant(serializer<_T>::underlying_type)
            , m_value(move(__value))
        {}

        virtual ~json_value() override;
    public:
        template <class _T>
        _T&& operator|(_T&& __default) const
            { return as(forward<_T>(__default)); }
    public:
        virtual String serialize() override;
    public:
        template <class _T>
        _T&& as(_T&& __default = _T()) const;

        template <class _T>
        void set_value(_T) const;
    private:
        underlying_type m_value;
    };
}

#include "json/json_value.ipp"

#endif // PMSCORE_JSON_JSON_VALUE_HPP

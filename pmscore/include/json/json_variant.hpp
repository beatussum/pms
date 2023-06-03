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


#ifndef PMSCORE_JSON_JSON_VARIANT_HPP
#define PMSCORE_JSON_JSON_VARIANT_HPP

#include "arduino/arduino.hpp"
#include "json/json_type.hpp"
#include "json/serializer.hpp"

namespace pmscore::json
{
    class json_variant
    {
        friend bool operator==(const json_variant&, const json_variant&);
        friend bool operator!=(const json_variant&, const json_variant&);
    public:
        json_variant(const json_variant&) noexcept = default;
        json_variant(json_variant&&) noexcept = default;

        json_variant(json_type __type) noexcept
            : m_type(__type)
        {}

        virtual ~json_variant() = default;

        virtual json_variant* clone() const = 0;
    public:
        json_variant& operator=(const json_variant&) noexcept = default;
        json_variant& operator=(json_variant&&) noexcept = default;
    public:
        virtual String serialize() = 0;
    public:
        json_type get_type() const noexcept { return m_type; }

        bool is(json_type __type) const noexcept { return (__type == m_type); }

        template <class _T>
        bool is() const noexcept
            { return is(serializer<_T>::underlying_type); }
    protected:
        json_type m_type;
    };

    bool operator==(const json_variant&, const json_variant&);

    inline bool operator!=(const json_variant& __l, const json_variant& __r)
        { return !(__l == __r); }
}

#endif // PMSCORE_JSON_JSON_VARIANT_HPP

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


#ifndef PMSCORE_JSON_JSON_PROPERTY_HPP
#define PMSCORE_JSON_JSON_PROPERTY_HPP

#include "core/utility.hpp"
#include "json/json_variant.hpp"

namespace pmscore::json
{
    class json_property : public json_variant
    {
        friend void swap(json_property&, json_property&) noexcept;

        friend bool operator==(const json_property&, const json_property&);
        friend bool operator!=(const json_property&, const json_property&);
    public:
        json_property() noexcept
            : json_variant(json_type::Property)

            , m_name()
            , m_value(nullptr)
        {}

        json_property(const json_property& __j)
            : json_variant(__j)

            , m_name(__j.m_name)
            , m_value(__j.m_value->clone())
        {}

        json_property(json_property&&);

        explicit json_property(
            String __name,
            const json_variant& __value
        ) noexcept

            : json_variant(json_type::Property)

            , m_name(move(__name))
            , m_value(__value.clone())
        {}

        ~json_property() override { delete m_value; }

        json_variant* clone() const override
            { return new json_property(*this); }
    public:
        json_property& operator=(json_property) noexcept;
    public:
        String serialize() override
            { return '"' + m_name + "\": " + m_value->serialize(); }
    public:
        String get_name() const { return m_name; }
        void set_name(String __n) { m_name = move(__n); }

        json_variant* get_value() noexcept { return m_value;  }
        const json_variant* get_value() const noexcept { return m_value;  }
        void set_value(const json_variant& __v) { m_value = __v.clone(); }
    private:
        String        m_name;
        json_variant* m_value;
    };

    void swap(json_property&, json_property&) noexcept;

    inline bool operator==(const json_property& __l, const json_property& __r)
        { return (__l.m_name == __r.m_name) && (__l.m_value == __r.m_value); }

    inline bool operator!=(const json_property& __l, const json_property& __r)
        { return !(__l == __r); }
}

#endif // PMSCORE_JSON_JSON_LIVE_ITERABLE_HPP

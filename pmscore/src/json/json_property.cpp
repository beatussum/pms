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


#include "json/json_property.hpp"

namespace pmscore::json
{
    void swap(json_property& __l, json_property& __r) noexcept
    {
        String name         = __l.m_name;
        json_type type      = __l.m_type;
        json_variant* value = __l.m_value;

        __l.m_name  = __r.m_name;
        __l.m_type  = __r.m_type;
        __l.m_value = __r.m_value;

        __r.m_name  = name;
        __r.m_type  = type;
        __r.m_value = value;
    }

    json_property::json_property(json_property&& __j)
        : json_variant(__j)

        , m_name(__j.m_name)
        , m_value(__j.m_value)
    {
        __j.m_name  = String();
        __j.m_value = nullptr;
    }

    json_property& json_property::operator=(json_property __j) noexcept
    {
        swap(*this, __j);

        return *this;
    }
}

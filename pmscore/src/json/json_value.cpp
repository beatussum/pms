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


#include "json/json_value.hpp"

namespace pmscore::json
{
    String json_value::serialize()
    {
        switch (get_type()) {
            case json_type::Boolean:
                return (m_value.as_bool ? "true" : "false");
            case json_type::Char:
                return String(m_value.as_char);
            case json_type::Float:
                return String(m_value.as_float);
            case json_type::SignedInteger:
                return String(m_value.as_int);
            case json_type::UnsignedInteger:
                return String(m_value.as_uint);
            default:
                return "null";
        }
    }
}

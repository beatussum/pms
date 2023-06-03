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
    bool operator==(const json_value& __l, const json_value& __r)
    {
        if (__l.m_type == __r.m_type) {
            switch (__l.m_type) {
                case json_type::Boolean:
                    return (__l.m_value.as_bool == __r.m_value.as_bool);
                case json_type::Char:
                    return (__l.m_value.as_char == __r.m_value.as_char);
                case json_type::Null:
                    return true;
                case json_type::Float:
                    return (__l.m_value.as_float == __r.m_value.as_float);
                case json_type::SignedInteger:
                    return (__l.m_value.as_int == __r.m_value.as_int);
                case json_type::String:
                    return (__l.m_value.as_string == __r.m_value.as_string);
                case json_type::UnsignedInteger:
                    return (__l.m_value.as_uint == __r.m_value.as_uint);
                default:
                    return false;
            }
        } else {
            return false;
        }
    }

    void json_value::__copy_value(const json_value& __j)
    {
        json_variant::operator=(__j);

        switch (m_type) {
            case json_type::Boolean:
            case json_type::Char:
            case json_type::Float:
            case json_type::SignedInteger:
            case json_type::UnsignedInteger:
                memcpy(&m_value, &__j.m_value, sizeof(underlying_type));

                break;
            default:
                break;
        }
    }

    json_value& json_value::operator=(const json_value& __j)
    {
        if (m_type == json_type::String) {
            if (__j.m_type == json_type::String) {
                m_value.as_string = __j.m_value.as_string;
            } else {
                m_value.as_string.~String();
            }
        }

        __copy_value(__j);

        return *this;
    }

    json_value& json_value::operator=(json_value&& __j)
    {
        if (m_type == json_type::String) {
            if (__j.m_type == json_type::String) {
                m_value.as_string = move(__j.m_value.as_string);
            } else {
                m_value.as_string.~String();
            }
        }

        __copy_value(__j);

        return *this;
    }

    String json_value::serialize()
    {
        switch (m_type) {
            case json_type::Boolean:
                return (m_value.as_bool ? "true" : "false");
            case json_type::Char:
                return String(m_value.as_char);
            case json_type::Float:
                return String(m_value.as_float);
            case json_type::SignedInteger:
                return String(m_value.as_int);
            case json_type::String:
                return m_value.as_string;
            case json_type::UnsignedInteger:
                return String(m_value.as_uint);
            default:
                return "null";
        }
    }
}

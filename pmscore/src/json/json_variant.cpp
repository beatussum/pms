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


#include "json/json_iterable.hpp"
#include "json/json_property.hpp"
#include "json/json_value.hpp"

namespace pmscore::json
{
    bool operator==(const json_variant& __l, const json_variant& __r)
    {
        if (__l.m_type == __r.m_type) {
            switch (__l.m_type) {
                case json_type::Boolean:
                case json_type::Char:
                case json_type::Float:
                case json_type::SignedInteger:
                case json_type::String:
                case json_type::UnsignedInteger:
                    return (
                        static_cast<const json_value&>(__l) ==
                        static_cast<const json_value&>(__r)
                    );
                case json_type::Null:
                    return true;
                case json_type::Array:
                case json_type::Object:
                    if (
                        static_cast<const json_basic_iterable&>(__l)
                        .is_live() ||

                        static_cast<const json_basic_iterable&>(__r)
                        .is_live()
                    )
                    {
                        return false;
                    } else {
                        return (
                            static_cast<const json_iterable&>(__l) ==
                            static_cast<const json_iterable&>(__r)
                        );
                    }
                case json_type::Property:
                    return (
                        static_cast<const json_property&>(__l) ==
                        static_cast<const json_property&>(__r)
                    );
            }
        } else {
            return false;
        }
    }
}

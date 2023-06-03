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


#include "math/vector.hpp"

#include "json/json_object.hpp"
#include "json/json_property.hpp"
#include "json/json_value.hpp"

namespace pmscore
{
    vector::operator pmscore::json::json_object() const
    {
        return pmscore::json::json_object({
            json::json_property("x", json::json_value(x)),
            json::json_property("y", json::json_value(y)),
        });
    }
}

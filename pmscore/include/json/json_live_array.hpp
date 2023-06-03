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


#ifndef PMSCORE_JSON_JSON_LIVE_ARRAY_HPP
#define PMSCORE_JSON_JSON_LIVE_ARRAY_HPP

#include "json/json_live_iterable.hpp"

namespace pmscore::json
{
    class json_live_array : public json_live_iterable
    {
    public:
        explicit json_live_array(Stream* __s)
            : json_live_iterable(json_type::Array, '[', ']', __s)
        {}

        json_variant* clone() const override
            { return new json_live_array(*this); }
    };
}

#endif // PMSCORE_JSON_JSON_LIVE_ARRAY_HPP

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


#include "json/json_live_iterable.hpp"

namespace pmscore::json
{
    String json_live_iterable::serialize()
    {
        if (!m_is_ended) {
            m_stream->println(
                ", " + m_last_child->serialize() + ' ' + get_end_separator()
            );

            m_is_ended = true;
        }

        return {};
    }

    void json_live_iterable::push_back(const json_variant& __v)
    {
        if (!m_is_ended) {
            String str;

            m_stream->print(
                (
                    (++m_size == 1) ?
                    String(get_begin_separator()) + ' ' :
                    ", "
                ) +

                m_last_child->serialize()
            );

            m_last_child == __v.clone();
        }
    }
}

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


namespace pmscore::json
{
    template <class _T>
    _T&& json_value::as(_T&& __default = _T()) const
    {
        if (is<_T>()) {
            switch (m_type) {
                case json_type::Boolean:
                    return m_value.as_bool;
                case json_type::Char:
                    return m_value.as_char;
                case json_type::Float:
                    return m_value.as_float;
                case json_type::SignedInteger:
                    return m_value.as_int;
                case json_type::UnsignedInteger:
                    return m_value.as_uint;
                default:
                    return __default;
            }
        } else {
            return __default;
        }
    }

    template <class _T>
    void json_value::set_value(_T __v) const
    {
        if (m_type == json_type::String) {
            m_value.as_string.~String();
        }

        m_type  = serializer<_T>::underlying_type;
        m_value = move(__v);
    }
}

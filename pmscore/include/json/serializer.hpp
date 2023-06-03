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


#ifndef PMSCORE_JSON_SERIALIZER_HPP
#define PMSCORE_JSON_SERIALIZER_HPP

#include "json/json_type.hpp"

namespace pmscore::json
{
    template <class _T>
    struct serializer
    {
        using type                                 = _T;
        static constexpr json_type underlying_type = json_type::Null;
    };

    template <>
    struct serializer<bool>
    {
        using type                                 = bool;
        static constexpr json_type underlying_type = json_type::Boolean;
    };

    template <>
    struct serializer<short>
    {
        using type                                 = short;
        static constexpr json_type underlying_type = json_type::SignedInteger;
    };

    template <>
    struct serializer<int>
    {
        using type                                 = int;
        static constexpr json_type underlying_type = json_type::SignedInteger;
    };

    template <>
    struct serializer<long>
    {
        using type                                 = long;
        static constexpr json_type underlying_type = json_type::SignedInteger;
    };

    template <>
    struct serializer<unsigned short>
    {
        using type = unsigned short;

        static constexpr json_type underlying_type =
            json_type::UnsignedInteger;
    };

    template <>
    struct serializer<unsigned int>
    {
        using type = unsigned int;

        static constexpr json_type underlying_type
            = json_type::UnsignedInteger;
    };

    template <>
    struct serializer<unsigned long>
    {
        using type = unsigned long;

        static constexpr json_type underlying_type =
            json_type::UnsignedInteger;
    };

    template <>
    struct serializer<char>
    {
        using type                                 = char;
        static constexpr json_type underlying_type = json_type::Char;
    };

    template <>
    struct serializer<signed char>
    {
        using type                                 = char;
        static constexpr json_type underlying_type = json_type::Char;
    };

    template <>
    struct serializer<unsigned char>
    {
        using type                                 = char;
        static constexpr json_type underlying_type = json_type::Char;
    };

    template <>
    struct serializer<String>
    {
        using type                                 = String;
        static constexpr json_type underlying_type = json_type::String;
    };
}

#endif // PMSCORE_JSON_SERIALIZER_HPP

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


#ifndef PMSCORE_JSON_JSON_LIVE_ITERABLE_HPP
#define PMSCORE_JSON_JSON_LIVE_ITERABLE_HPP

#include "json/json_basic_iterable.hpp"

namespace pmscore::json
{
    class json_live_iterable : public json_basic_iterable
    {
    public:
        json_live_iterable(const json_live_iterable&) = default;
        json_live_iterable(json_live_iterable&&) = default;

        explicit json_live_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator,
            Stream* __s
        )
            : json_basic_iterable(
                __type,
                __begin_separator,
                __end_separator,
                0
            )

            , m_stream(__s)
            , m_is_ended(false)
            , m_last_child(nullptr)
        {}

        virtual ~json_live_iterable() override { delete m_last_child; }

        virtual json_variant* clone() const override
            { return new json_live_iterable(*this); }
    public:
        json_live_iterable& operator=(const json_live_iterable&) = default;
        json_live_iterable& operator=(json_live_iterable&&) = default;
    public:
        virtual String serialize() override;
    public:
        void push_back(const json_variant& __v);
    public:
        bool is_ended() const noexcept { return m_is_ended; }

        reference_type get_last_child() noexcept { return *m_last_child; }

        const_reference_type get_last_child() const noexcept
            { return *m_last_child; }
    private:
        Stream* m_stream;

        bool          m_is_ended;
        json_variant* m_last_child;
    };
}

#endif // PMSCORE_JSON_JSON_LIVE_ITERABLE_HPP

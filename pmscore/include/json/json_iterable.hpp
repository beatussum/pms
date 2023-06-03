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


#ifndef PMSCORE_JSON_JSON_ITERABLE_HPP
#define PMSCORE_JSON_JSON_ITERABLE_HPP

#include "json/json_basic_iterable.hpp"

namespace pmscore::json
{
    class json_iterable : public json_basic_iterable
    {
        friend void swap(json_iterable&, json_iterable&) noexcept;

        friend bool operator==(const json_iterable&, const json_iterable&);
        friend bool operator!=(const json_iterable&, const json_iterable&);
    public:
        using iterator        = json_variant**;
        using const_iterator  = const json_variant *const *;
        using difference_type = ptrdiff_t;
    public:
        explicit json_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator,
            size_t __n
        )
            : json_basic_iterable(
                __type,
                __begin_separator,
                __end_separator,
                0
            )

            , m_values(new json_variant*[__n])

            , m_reserved_size(__n)
        {}

        json_iterable() noexcept
            : json_iterable(json_type::Null, 0, 0)
        {}

        json_iterable(const json_iterable&);
        json_iterable(json_iterable&&) noexcept;

        explicit json_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator
        ) noexcept
            : json_basic_iterable(
                __type,
                __begin_separator,
                __end_separator,
                0
            )

            , m_values(nullptr)

            , m_reserved_size(0)
        {}

        explicit json_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator,
            const json_variant* __values,
            size_t __n
        );

        template <class _T, size_t _n>
        explicit json_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator,
            const _T (&__values)[_n]
        )
            : json_iterable(
                __type,
                __begin_separator,
                __end_separator,
                __values,
                _n
            )
        {}

        explicit json_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator,
            const_iterator __begin,
            const_iterator __end
        );

        explicit json_iterable(
            json_type __type,
            char __begin_separator,
            char __end_separator,
            size_t __n,
            const json_variant& __value
        );

        ~json_iterable() override { clear(); }

        json_variant* clone() const override
            { return new json_iterable(*this); }
    public:
        json_iterable& operator=(json_iterable);
    public:
        reference_type operator[](size_t __n) noexcept
            { return m_values[__n]; }

        const_reference_type operator[](size_t __n) const noexcept
            { return m_values[__n]; }
    public:
        reference_type front() { return *begin(); }
        const_reference_type front() const { return *begin(); }

        reference_type back() { return end()[-1]; }
        const_reference_type back() const { return end()[-1]; }
    public:
        void assign(iterator, iterator);

        template <class _T, size_t _n>
        void assign(_T (&__v)[_n]) { assign(__v, __v + _n); }

        void assign(size_t, const json_variant&);

        void clear();

        iterator erase(iterator);
        iterator erase(iterator, iterator);

        void pop_back();
        void push_back(const json_variant&);
    public:
        String serialize() override;
    public:
        bool is_live() const noexcept final { return false; }
    public:
        iterator begin() { return m_values; }
        const_iterator begin() const { return m_values; }
        const_iterator cbegin() const { return m_values; }

        iterator end() { return (m_values + m_size); }
        const_iterator end() const { return (m_values + m_size); }
        const_iterator cend() const { return (m_values + m_size); }
    private:
        iterator m_values;

        size_t m_reserved_size;
    };

    void swap(json_iterable&, json_iterable&) noexcept;
    bool operator==(const json_iterable&, const json_iterable&);

    inline bool operator!=(const json_iterable& __l, const json_iterable& __r)
        { return !(__l == __r); }
}

#endif // PMSCORE_JSON_JSON_ITERABLE_HPP

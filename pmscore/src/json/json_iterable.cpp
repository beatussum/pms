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

#include "core/iterator.hpp"

namespace pmscore::json
{
    void swap(json_iterable& __l, json_iterable& __r) noexcept
    {
        json_iterable::iterator values = __l.m_values;
        size_t reserved_size           = __l.m_reserved_size;

        __l.m_values        = __r.m_values;
        __l.m_reserved_size = __r.m_reserved_size;

        __r.m_values        = values;
        __r.m_reserved_size = reserved_size;
    }

    bool operator==(const json_iterable& __l, const json_iterable& __r)
    {
        if (__l.size() == __r.size()) {
            json_iterable::const_iterator i = __l.cbegin();
            json_iterable::const_iterator j = __r.cbegin();

            while (i != __l.end()) {
                if (**i != **j) {
                    return false;
                }

                ++i, ++j;
            }

            return true;
        } else {
            return false;
        }
    }

    json_iterable::json_iterable(const json_iterable& __j) noexcept
        : json_basic_iterable(
            __j.m_type,
            __j.get_begin_separator(),
            __j.get_end_separator(),
            __j.m_size
        )

        , m_values(new json_variant*[__j.m_size])

        , m_reserved_size(__j.m_size)
    {
        iterator i       = begin();
        const_iterator j = __j.cbegin();

        while (i != end()) {
            *i = (*j)->clone();

            ++i, ++j;
        }
    }

    json_iterable::json_iterable(json_iterable&& __j) noexcept
        : json_basic_iterable(
            __j.m_type,
            __j.get_begin_separator(),
            __j.get_end_separator(),
            __j.m_size
        )

        , m_values(__j.m_values)

        , m_reserved_size(__j.m_reserved_size)
    {
        __j.m_size          = 0;
        __j.m_values        = nullptr;
        __j.m_reserved_size = 0;
    }

    json_iterable::json_iterable(
        json_type __type,
        char __begin_separator,
        char __end_separator,
        const json_variant* __values,
        size_t __n
    )
        : json_iterable(__type, __begin_separator, __end_separator, __n)
    {
        for (iterator i = begin(); i != end(); ++i, ++__values) {
            *i = __values->clone();
        }
    }

    json_iterable::json_iterable(
        json_type __type,
        char __begin_separator,
        char __end_separator,
        const_iterator __begin,
        const_iterator __end
    )
        : json_iterable(
            __type,
            __begin_separator,
            __end_separator,
            __end - __begin
        )
    {
        for (iterator i = begin(); __begin != __end; ++i, ++__begin) {
            *i = (*__begin)->clone();
        }
    }

    json_iterable::json_iterable(
        json_type __type,
        char __begin_separator,
        char __end_separator,
        size_t __n,
        const json_variant& __value
    )
        : json_iterable(__type, __begin_separator, __end_separator, __n)
    {
        for (iterator i = begin(); i != end(); ++i) {
            *i = __value.clone();
        }
    }

    json_iterable& json_iterable::operator=(json_iterable __j)
    {
        swap(*this, __j);

        return *this;
    }

    void json_iterable::assign(iterator __ia, iterator __ib)
    {
        size_t size = (__ib - __ia);

        if (size > m_reserved_size) {
            clear();

            m_values = new json_variant*[size];

            for (iterator i = begin(); __ia != __ib; ++i, ++__ia) {
                *i = (*__ia)->clone();
            }

            m_reserved_size = size;
        } else {
            for (iterator i = begin(); __ia != __ib; ++i, ++__ia) {
                delete *i;

                *i = (*__ia)->clone();
            }
        }

        m_size = size;
    }

    void json_iterable::assign(size_t __n, const json_variant& __v)
    {
        if (__n > m_reserved_size) {
            clear();

            m_values = new json_variant*[__n];

            for (iterator i = begin(); __n != 0; --__n, ++i) {
                *i = __v.clone();
            }

            m_reserved_size = __n;
        } else {
            for (iterator i = begin(); __n != 0; --__n, ++i) {
                delete *i;

                *i = __v.clone();
            }
        }

        m_size = __n;
    }

    void json_iterable::clear()
    {
        for (iterator i = begin(); i != end(); ++i) {
            delete *i;
        }

        delete[] m_values;

        m_values = nullptr;
    }

    json_iterable::iterator json_iterable::erase(iterator __i)
    {
        delete *__i;

        copy(__i + 1, end(), __i);

        --m_size;

        return __i;
    }

    json_iterable::iterator json_iterable::erase(iterator __ia, iterator __ib)
    {
        m_size -= (__ib - __ia);

        for (; __ia < __ib; ++__ia, --__ib) {
            delete *__ia;

            *__ia = *__ib;
        }

        return ++__ia;
    }

    void json_iterable::pop_back()
    {
        if (!empty()) {
            delete end()[-1];

            --m_size;
        }
    }

    void json_iterable::push_back(const json_variant& __v)
    {
        if (m_reserved_size == m_size) {
            iterator tmp = new json_variant*[m_size + 1];

            if (!empty()) {
                copy(begin(), end(), tmp);

                delete[] m_values;
            }

            m_values = tmp;

            ++m_reserved_size;
        }

        *end() = __v.clone();
        ++m_size;
    }

    String json_iterable::serialize()
    {
        String ret(get_begin_separator());

        if (!empty()) {
            for (iterator i = begin(); i != (end() - 1); ++i) {
                ret += ((*i)->serialize() + ", ");
            }

            ret += end()[-1]->serialize();
        }

        return (ret += get_end_separator());
    }
}

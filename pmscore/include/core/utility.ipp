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


namespace pmscore
{
    /***********
     * forward *
     ***********/

    template <class _T>
    constexpr _T&& forward(remove_reference_t<_T>&& __t) noexcept
    {
        static_assert(
            !is_lvalue_reference_v<_T>,
            "std::forward must not be used to convert an rvalue to an lvalue"
        );

        return static_cast<_T&&>(__t);
    }
}

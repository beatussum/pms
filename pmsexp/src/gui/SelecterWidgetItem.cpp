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


#include "gui/SelecterWidgetItem.hpp"

namespace gui
{
    SelecterWidgetItem::SelecterWidgetItem(
        const QIcon& __i,
        const QString& __txt,
        QListWidget* __parent,
        int __type
    )
        : QListWidgetItem(__i, __txt, __parent, __type)
    {
        __set_properties();
    }

    SelecterWidgetItem::SelecterWidgetItem(
        const QString& __txt,
        QListWidget* __parent,
        int __type
    )
        : QListWidgetItem(__txt, __parent, __type)
    {
        __set_properties();
    }

    SelecterWidgetItem::SelecterWidgetItem(QListWidget* __parent, int __type)
        : QListWidgetItem(__parent, __type)
    {
        __set_properties();
    }

    void SelecterWidgetItem::__set_properties()
    {
        QListWidget* parent = listWidget();

        if (parent != nullptr) {
            setSizeHint({parent->sizeHint().width(), 96});
        }
    }
}

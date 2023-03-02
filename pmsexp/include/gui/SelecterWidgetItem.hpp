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


#ifndef PMSEXP_GUI_SELECTER_WIDGET_ITEM_HPP
#define PMSEXP_GUI_SELECTER_WIDGET_ITEM_HPP

#include <QtWidgets/QListWidgetItem>

namespace gui
{
    class SelecterWidgetItem : public QListWidgetItem
    {
    public:
        explicit SelecterWidgetItem(
            const QIcon&,
            const QString& __txt,
            QListWidget* __parent = nullptr,
            int __type = QListWidgetItem::Type
        );

        explicit SelecterWidgetItem(
            const QString& __txt,
            QListWidget* __parent = nullptr,
            int __type = QListWidgetItem::Type
        );

        explicit SelecterWidgetItem(
            QListWidget* __parent = nullptr,
            int __type = QListWidgetItem::Type
        );
    private:
        void __set_properties();
    };
}

#endif // PMSEXP_GUI_SELECTER_WIDGET_ITEM_HPP

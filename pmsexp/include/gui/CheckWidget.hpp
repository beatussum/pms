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


#ifndef PMSEXP_GUI_CHECK_WIDGET_HPP
#define PMSEXP_GUI_CHECK_WIDGET_HPP

#include "gui/ItemizeWidget.hpp"

namespace gui
{
    class CheckWidget : public ItemizeWidget
    {
        Q_OBJECT
        Q_PROPERTY(bool status READ get_status WRITE set_status)

    public:
        explicit CheckWidget(
            QString __info,
            bool __status       = false,
            QWidget* __parent   = nullptr,
            Qt::WindowFlags __f = {}
        )
            : ItemizeWidget(
                std::move(__info),
                QIcon::fromTheme(__status ? "list-add" : "list-remove"),
                __parent,
                __f
            )

            , m_status(__status)
        {}

        CheckWidget(QWidget* __parent = nullptr, Qt::WindowFlags __f = {})
            : CheckWidget(QString(), false, __parent, __f)
        {}
    public:
        bool get_status() const noexcept { return m_status; }
    public slots:
        void set_status(bool);
    private:
        bool m_status;
    };
}

#endif // PMSEXP_GUI_CHECK_WIDGET_HPP

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


#include "gui/ItemizeWidget.hpp"

#include <QtGui/QIcon>

namespace gui
{
    ItemizeWidget::ItemizeWidget(
        QString __info,
        bool __status,
        QWidget* __parent,
        Qt::WindowFlags __f
    )
        : QWidget(__parent, __f)
        , m_status(__status)
        , m_ui(new Ui::ItemizeWidget())
    {
        m_ui->setupUi(this);
        __set_status(m_status);
        set_info(__info);
    }

    ItemizeWidget::~ItemizeWidget()
    {
        delete m_ui;
    }

    void ItemizeWidget::__set_status(bool __s)
    {
        m_ui->m_check_label->setPixmap(
            QIcon::fromTheme(
                __s ? "list-add" : "list-remove"
            ).pixmap({32, 32})
        );
    }
}

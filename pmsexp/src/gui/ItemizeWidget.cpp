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

namespace gui
{
    ItemizeWidget::ItemizeWidget(
        QString __info,
        QPixmap __p,
        QWidget* __parent,
        Qt::WindowFlags __f
    )
        : QWidget(__parent, __f)
        , m_ui(new Ui::ItemizeWidget())
    {
        m_ui->setupUi(this);
        set_info(__info);
        set_pixmap(__p);
    }

    QPixmap ItemizeWidget::get_pixmap() const
    {
        return m_ui->m_pixmap_label->pixmap(Qt::ReturnByValueConstant());
    }

    void ItemizeWidget::set_pixmap(QPixmap __p)
    {
        m_ui->m_pixmap_label->setPixmap(__p);
    }

    void ItemizeWidget::set_pixmap(const QIcon& __i)
    {
        set_pixmap(__i.pixmap({32, 32}));
    }

    void ItemizeWidget::clear()
    {
        m_ui->m_pixmap_label->clear();
        m_ui->m_info_label->clear();
    }
}

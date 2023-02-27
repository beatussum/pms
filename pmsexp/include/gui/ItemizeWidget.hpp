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


#ifndef PMSEXP_GUI_ITEMIZE_WIDGET_HPP
#define PMSEXP_GUI_ITEMIZE_WIDGET_HPP

#include "ui_ItemizeWidget.h"

#include <QtGui/QIcon>

namespace gui
{
    class ItemizeWidget : public QWidget
    {
        Q_OBJECT

        Q_PROPERTY(
            QString info
            READ get_info
            WRITE set_info
            RESET clear
            STORED false
            REQUIRED
        )

        Q_PROPERTY(
            QPixmap pixmap
            READ get_pixmap
            WRITE set_pixmap
            RESET clear
            STORED false
            REQUIRED
        )

    public:
        explicit ItemizeWidget(
            QString __info,
            QPixmap,
            QWidget* __parent = nullptr,
            Qt::WindowFlags = Qt::WindowFlags()
        );

        explicit ItemizeWidget(
            QString __info,
            const QIcon& __i,
            QWidget* __parent = nullptr,
            Qt::WindowFlags __f = Qt::WindowFlags()
        )
            : ItemizeWidget(
                std::move(__info),
                __i.pixmap({32, 32}),
                __parent,
                __f
            )
        {}

        virtual ~ItemizeWidget() { delete m_ui; }
    public:
        QString get_info() const { return m_ui->m_info_label->text(); }
        QPixmap get_pixmap() const;
    public slots:
        void set_info(QString __i) { m_ui->m_info_label->setText(__i); }
    protected slots:
        void set_pixmap(QPixmap);
        void set_pixmap(const QIcon&);

        void clear();
    private:
        Ui::ItemizeWidget* m_ui;
    };
}

#endif // PMSEXP_GUI_ITEMIZE_WIDGET_HPP

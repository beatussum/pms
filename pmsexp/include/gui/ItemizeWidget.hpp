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

namespace gui
{
    class ItemizeWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit ItemizeWidget(
            QString __info,
            bool __status = false,
            QWidget* __parent = nullptr,
            Qt::WindowFlags __f = Qt::WindowFlags()
        );

        virtual ~ItemizeWidget() { delete m_ui; }
    private:
        void __set_status(bool);
    public:
        bool get_status() const noexcept { return m_status; }
        QString get_info() const { return m_ui->m_info_label->text(); }
    public slots:
        void set_info(QString __i) { m_ui->m_info_label->setText(__i); }
        void set_status(bool __s) { __set_status(m_status = __s); }
    private:
        bool               m_status;
        Ui::ItemizeWidget* m_ui;
    };
}

#endif // PMSEXP_GUI_ITEMIZE_WIDGET_HPP

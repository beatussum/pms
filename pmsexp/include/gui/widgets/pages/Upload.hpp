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


#ifndef PMSEXP_GUI_WIDGETS_PAGES_UPLOAD_HPP
#define PMSEXP_GUI_WIDGETS_PAGES_UPLOAD_HPP

#include "ui_Upload.h"

namespace gui::widgets::pages
{
    class Upload : public QWidget
    {
        Q_OBJECT

        Q_PROPERTY(
            bool upload_status
            READ is_upload_valid
            RESET reset_upload_status
            NOTIFY upload_status_changed
            STORED false
        )

    public:
        explicit Upload(QWidget* __parent = nullptr, Qt::WindowFlags = {});
        virtual ~Upload() { delete m_ui; }
    public:
        bool is_upload_valid() const;
    signals:
        void upload_status_changed();
    private slots:
        void update_upload_status();
    public slots:
        void reset_upload_status();
    private:
        Ui::Upload* m_ui;
    };
}

#endif // PMSEXP_GUI_WIDGETS_PAGES_UPLOAD_HPP
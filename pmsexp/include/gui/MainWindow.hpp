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


#ifndef PMSEXP_GUI_MAIN_WINDOW_HPP
#define PMSEXP_GUI_MAIN_WINDOW_HPP

#include "ui_MainWindow.h"

namespace gui
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        Q_PROPERTY(
            bool ex_upload_status
            READ has_ex_uploaded
            RESET reset_ex_status
            NOTIFY ex_uploaded
            STORED false
        )

        Q_PROPERTY(
            bool th_upload_status
            READ has_th_uploaded
            RESET reset_th_status
            NOTIFY th_uploaded
            STORED false
        )

        Q_PROPERTY(
            bool upload_status
            READ is_upload_valid
            RESET reset_upload_status
            NOTIFY upload_status_changed
            STORED false
        )

    public:
        explicit MainWindow(QWidget* __parent = nullptr, Qt::WindowFlags = {});
        virtual ~MainWindow() { delete m_ui; }
    public:
        bool has_ex_uploaded() const;
        bool has_th_uploaded() const;
        bool is_upload_valid() const;
    signals:
        void ex_uploaded();
        void th_uploaded();
        void upload_status_changed();
    public slots:
        void reset_ex_status() { m_ui->m_ex_uploader->reset_file_path(); }
        void reset_th_status() { m_ui->m_th_uploader->reset_file_path(); }
        void reset_upload_status();

        void previous();
        void valid();
    private slots:
        void update_upload_status();
    private:
        Ui::MainWindow* m_ui;
    };
}

#endif // PMSEXP_GUI_MAIN_WINDOW_HPP

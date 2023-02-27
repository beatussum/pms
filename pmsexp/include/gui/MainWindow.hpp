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

    public:
        explicit MainWindow(QWidget* __parent = nullptr, Qt::WindowFlags = {});
        virtual ~MainWindow() { delete m_ui; }
    protected slots:
        void when_action_reset_triggered();
        void when_return_button_clicked();
        void when_uploader_update();
        void when_valid_button_clicked();
    private:
        Ui::MainWindow* m_ui;
    };
}

#endif // PMSEXP_GUI_MAIN_WINDOW_HPP

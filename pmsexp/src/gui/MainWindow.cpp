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


#include "gui/MainWindow.hpp"

namespace gui
{
    MainWindow::MainWindow(QWidget* __parent, Qt::WindowFlags __f)
        : QMainWindow(__parent, __f)
        , m_ui(new Ui::MainWindow())
    {
        m_ui->setupUi(this);

        QObject::connect(
            m_ui->m_action_reset,
            &QAction::triggered,
            this,
            &MainWindow::when_action_reset_triggered
        );

        QObject::connect(
            m_ui->m_return_button,
            &QPushButton::clicked,
            this,
            &MainWindow::when_return_button_clicked
        );

        QObject::connect(
            m_ui->m_ex_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::when_uploader_update
        );

        QObject::connect(
            m_ui->m_th_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::when_uploader_update
        );

        QObject::connect(
            m_ui->m_valid_button,
            &QPushButton::clicked,
            this,
            &MainWindow::when_valid_button_clicked
        );
    }

    void MainWindow::when_action_reset_triggered()
    {
        m_ui->m_ex_uploader->reset_file_path();
        m_ui->m_th_uploader->reset_file_path();
    }

    void MainWindow::when_return_button_clicked()
    {
        m_ui->m_stacked_widget->setCurrentIndex(0);
    }

    void MainWindow::when_uploader_update()
    {
        bool ex_status = !m_ui->m_ex_uploader->is_empty();
        bool th_status = !m_ui->m_th_uploader->is_empty();

        m_ui->m_ex_item->set_status(ex_status);
        m_ui->m_th_item->set_status(th_status);
        m_ui->m_valid_button->setEnabled(ex_status && th_status);
    }

    void MainWindow::when_valid_button_clicked()
    {
        m_ui->m_stacked_widget->setCurrentIndex(1);
    }
}

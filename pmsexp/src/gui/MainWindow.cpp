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
            m_ui->m_ex_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::ex_uploaded
        );

        QObject::connect(
            m_ui->m_th_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::th_uploaded
        );

        QObject::connect(
            m_ui->m_ex_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::upload_status_changed
        );

        QObject::connect(
            m_ui->m_th_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::upload_status_changed
        );

        QObject::connect(
            m_ui->m_action_reset,
            &QAction::triggered,
            this,
            &MainWindow::reset_upload_status
        );

        QObject::connect(
            m_ui->m_return_button,
            &QPushButton::clicked,
            this,
            &MainWindow::previous
        );

        QObject::connect(
            m_ui->m_valid_button,
            &QPushButton::clicked,
            this,
            &MainWindow::valid
        );

        QObject::connect(
            m_ui->m_ex_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::update_upload_status
        );

        QObject::connect(
            m_ui->m_th_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &MainWindow::update_upload_status
        );
    }

    bool MainWindow::has_ex_uploaded() const
    {
        return !m_ui->m_ex_uploader->is_empty();
    }

    bool MainWindow::has_th_uploaded() const
    {
        return !m_ui->m_th_uploader->is_empty();
    }

    bool MainWindow::is_upload_valid() const
    {
        return has_ex_uploaded() && has_th_uploaded();
    }

    void MainWindow::reset_upload_status()
    {
        reset_ex_status();
        reset_th_status();
    }

    void MainWindow::previous()
    {
        m_ui->m_stacked_widget->setCurrentIndex(0);
    }

    void MainWindow::valid()
    {
        if (is_upload_valid()) {
            m_ui->m_stacked_widget->setCurrentIndex(1);
        } else {
            throw std::runtime_error(
                "This `gui::MainWindow` object must have the `upload_status` "
                "property equal to `true` before calling `valid()`."
            );
        }
    }

    void MainWindow::update_upload_status()
    {
        bool ex_status = has_ex_uploaded();
        bool th_status = has_th_uploaded();

        m_ui->m_ex_item->set_status(ex_status);
        m_ui->m_th_item->set_status(th_status);
        m_ui->m_valid_button->setEnabled(ex_status && th_status);
    }
}

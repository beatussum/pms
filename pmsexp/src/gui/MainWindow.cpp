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

#include "gui/widgets/pages/Selection.hpp"
#include "gui/widgets/pages/Statistics.hpp"
#include "gui/widgets/pages/Upload.hpp"

namespace gui
{
    MainWindow::MainWindow(QWidget* __parent, Qt::WindowFlags __f)
        : QMainWindow(__parent, __f)
        , m_ui(new Ui::MainWindow())
        , m_selection_page(new widgets::pages::Selection())
        , m_statistics_page(new widgets::pages::Statistics())
        , m_upload_page(new widgets::pages::Upload())
    {
        m_ui->setupUi(this);

        m_ui->m_central_widget->add_page(m_upload_page);
        m_ui->m_central_widget->add_page(m_selection_page);
        m_ui->m_central_widget->add_page(m_statistics_page);

        QObject::connect(
            m_upload_page,
            &widgets::pages::Upload::upload_status_changed,
            this,
            &MainWindow::update_progess
        );

        QObject::connect(
            m_selection_page->get_selection_widget(),
            &widgets::SelectionWidget::selection_changed,
            this,
            &MainWindow::update_progess
        );

        QObject::connect(
            m_ui->m_action_reset,
            &QAction::triggered,
            m_upload_page,
            &widgets::pages::Upload::reset_upload_status
        );

        QObject::connect(
            m_ui->m_action_reset,
            &QAction::triggered,
            m_selection_page->get_selection_widget(),
            &widgets::SelectionWidget::reset_selection
        );
    }

    MainWindow::~MainWindow()
    {
        delete m_ui;

        delete m_selection_page;
        delete m_statistics_page;
        delete m_upload_page;
    }

    void MainWindow::update_progess()
    {
        int progress = 0;

        if (m_upload_page->is_upload_valid()) {
            ++progress;

            if (m_selection_page->get_selection_widget()->has_selection()) {
                ++progress;
            }
        }

        m_ui->m_central_widget->set_progress(progress);
    }
}

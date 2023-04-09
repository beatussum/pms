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


#include "gui/widgets/pages/Upload.hpp"

namespace gui::widgets::pages
{
    Upload::Upload(QWidget* __parent, Qt::WindowFlags __f)
        : QWidget(__parent, __f)
        , m_ui(new Ui::Upload())
    {
        m_ui->setupUi(this);

        QObject::connect(
            m_ui->m_ex_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &Upload::upload_status_changed
        );

        QObject::connect(
            m_ui->m_th_uploader,
            &widgets::UploadWidget::file_path_updated,
            this,
            &Upload::upload_status_changed
        );

        QObject::connect(
            this,
            &Upload::upload_status_changed,
            this,
            &Upload::update_upload_status
        );
    }

    bool Upload::is_upload_valid() const
    {
        return
            !m_ui->m_ex_uploader->is_empty() &&
            !m_ui->m_th_uploader->is_empty();
    }

    void Upload::reset_upload_status()
    {
        m_ui->m_ex_uploader->reset_file_path();
        m_ui->m_th_uploader->reset_file_path();
    }

    void Upload::update_upload_status()
    {
        bool ex_status = !m_ui->m_ex_uploader->is_empty();
        bool th_status = !m_ui->m_th_uploader->is_empty();

        m_ui->m_ex_item->set_status(ex_status);
        m_ui->m_th_item->set_status(th_status);
    }
}
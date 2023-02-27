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


#include "gui/UploadWidget.hpp"

#include <QtCore/QMimeData>
#include <QtGui/QDragEnterEvent>

namespace gui
{
    UploadWidget::UploadWidget(
        QString __info,
        QWidget* __parent,
        Qt::WindowFlags __f
    )
        : ItemizeWidget(
                std::move(__info),
                QIcon::fromTheme("document-new"),
                __parent,
                __f
            )

        , m_file_path()
    {
        setAcceptDrops(true);
    }

    void UploadWidget::reset_file_path()
    {
        m_file_path.clear();

        emit file_path_updated(m_file_path);
    }

    void UploadWidget::dragEnterEvent(QDragEnterEvent* __e)
    {
        if (
            (__e->mimeData()->hasUrls()) &&
            (__e->mimeData()->urls().size() == 1)
        )
        {
            __e->acceptProposedAction();
        }

        ItemizeWidget::dragEnterEvent(__e);
    }

    void UploadWidget::dropEvent(QDropEvent* __e)
    {
        m_file_path = __e->mimeData()->urls().first().toLocalFile();

        emit file_path_updated(m_file_path);

        ItemizeWidget::dropEvent(__e);
    }
}

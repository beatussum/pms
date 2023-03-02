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


#ifndef PMSEXP_GUI_WIDGETS_UPLOAD_WIDGET_HPP
#define PMSEXP_GUI_WIDGETS_UPLOAD_WIDGET_HPP

#include "gui/widgets/ItemizeWidget.hpp"

namespace gui::widgets
{
    class UploadWidget : public ItemizeWidget
    {
        Q_OBJECT

        Q_PROPERTY(
            QString file_path
            READ get_file_path
            WRITE set_file_path
            RESET reset_file_path
            NOTIFY file_path_updated
        )

    public:
        explicit UploadWidget(
            QString __info,
            QWidget* __parent = nullptr,
            Qt::WindowFlags   = {}
        );

        UploadWidget(QWidget* __parent = nullptr, Qt::WindowFlags __f = {})
            : UploadWidget(QString(), __parent, __f)
        {}
    public:
        QString get_file_path() const { return m_file_path; }
        bool is_empty() const { return m_file_path.isEmpty(); }
    public slots:
        void set_file_path(QString);
        void reset_file_path();
    signals:
        void file_path_updated(const QString& __new_file_path);
    protected:
        virtual void dragEnterEvent(QDragEnterEvent*) override;
        virtual void dropEvent(QDropEvent*) override;
    private:
        QString m_file_path;
    };
}

#endif // PMSEXP_GUI_WIDGETS_UPLOAD_WIDGET_HPP

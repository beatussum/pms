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


#include "gui/widgets/SelectionWidget.hpp"

#include <QtGui/qevent.h>

namespace gui::widgets
{
    SelectionWidget::SelectionWidget(
        const QPixmap& __p,
        QWidget* __parent,
        Qt::WindowFlags __f
    )
        : QLabel(__parent, __f)
        , m_origin()
        , m_rubber_band(QRubberBand::Rectangle, this)
    {
        setPixmap(__p);
    }

    void SelectionWidget::set_selection(QRect __s) noexcept
    {
        m_selection = std::move(__s);

        emit selection_changed(m_selection);
    }

    void SelectionWidget::keyPressEvent(QKeyEvent* __e)
    {
        switch (__e->key()) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
                if (m_rubber_band.isVisible()) {
                    set_selection(m_rubber_band.geometry());
                }

                break;
            case Qt::Key_Escape:
                reset_selection();
                m_rubber_band.hide();

                break;
            default:
                QLabel::keyPressEvent(__e);

                break;
        }
    }

    void SelectionWidget::mousePressEvent(QMouseEvent* __e)
    {
        m_rubber_band.setGeometry(QRect((m_origin = __e->pos()), QSize()));
        m_rubber_band.show();

        QLabel::mousePressEvent(__e);
    }

    void SelectionWidget::mouseMoveEvent(QMouseEvent* __e)
    {
        m_rubber_band.setGeometry(
            QRect(m_origin, __e->pos()).normalized()
        );

        QLabel::mouseMoveEvent(__e);
    }

    void SelectionWidget::mouseReleaseEvent(QMouseEvent* __e)
    {
        QLabel::mouseReleaseEvent(__e);
    }
}

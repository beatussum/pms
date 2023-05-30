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
        , m_selection()
        , m_selected(false)
    {
        setAlignment(Qt::AlignCenter);
        setPixmap(__p);
    }

    void SelectionWidget::__update_rubber_band_geometry()
    {
        if (m_rubber_band.isVisible()) {
            m_rubber_band.move(
                get_pixmap_rect().topLeft() + m_selection.topLeft()
            );
        }
    }

    void SelectionWidget::keyPressEvent(QKeyEvent* __e)
    {
        switch (__e->key()) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
                if (
                    m_rubber_band.isVisible() &&
                    (m_selection.size() != QSize())
                )
                {
                    m_selected = true;

                    emit selection_changed(m_selection);
                }

                break;
            case Qt::Key_Escape:
                reset_selection();

                break;
            default:
                QLabel::keyPressEvent(__e);

                break;
        }
    }

    void SelectionWidget::mousePressEvent(QMouseEvent* __e)
    {
        QPoint origin = __e->pos();

        setFocus();

        if (get_pixmap_rect().contains(origin)) {
            if (m_selected) {
                reset_selection();
            }

            m_rubber_band.setGeometry(
                QRect(m_origin = std::move(origin), QSize())
            );

            m_rubber_band.show();
        }

        QLabel::mousePressEvent(__e);
    }

    void SelectionWidget::mouseMoveEvent(QMouseEvent* __e)
    {
        QPoint bottom_right = __e->pos();
        QRect pixmap_rect   = get_pixmap_rect();

        if (pixmap_rect.contains(bottom_right)) {
            QRect rubber_band_rect = QRect(
                m_origin,
                std::move(bottom_right)
            ).normalized();

            m_selection = QRect(
                rubber_band_rect.x() - pixmap_rect.x(),
                rubber_band_rect.y() - pixmap_rect.y(),
                rubber_band_rect.width(),
                rubber_band_rect.height()
            );

            m_rubber_band.setGeometry(std::move(rubber_band_rect));
        }

        QLabel::mouseMoveEvent(__e);
    }

    void SelectionWidget::resizeEvent(QResizeEvent* __e)
    {
        __update_rubber_band_geometry();

        QLabel::resizeEvent(__e);
    }

    void SelectionWidget::showEvent(QShowEvent* __e)
    {
        __update_rubber_band_geometry();

        QLabel::showEvent(__e);
    }

    QRect SelectionWidget::get_pixmap_rect() const
    {
        QRect ret = pixmap(Qt::ReturnByValue).rect();

        ret.moveTopLeft(
            QPoint(width() - ret.width(), height() - ret.height()) / 2
        );

        return ret;
    }

    void SelectionWidget::set_selection(QRect __s) noexcept
    {
        m_selection = std::move(__s);
        m_selected  = true;

        emit selection_changed(m_selection);
    }

    void SelectionWidget::reset_selection() noexcept
    {
        m_selection = QRect();
        m_selected  = false;

        m_rubber_band.hide();

        emit selection_changed(m_selection);
    }
}

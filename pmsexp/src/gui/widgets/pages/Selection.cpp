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


#include "gui/widgets/pages/Selection.hpp"

#include <QtGui/qevent.h>

namespace gui::widgets::pages
{
    Selection::Selection(
        const QPixmap& __p,
        QWidget* __parent,
        Qt::WindowFlags __f
    )
        : QWidget(__parent, __f)
        , m_ui(new Ui::Selection())
        , m_rubber_band(QRubberBand::Rectangle, this)
    {
        m_ui->setupUi(this);

        m_ui->m_help_label->setText(
            tr(
                "Utilisez la souris pour sélectionner la zone à monitorer. "
                "Appuyez sur « %1 » pour valider la sélection et « %2 » pour "
                "effacer la précédente."
            )
            .arg(QKeySequence(Qt::Key_Enter).toString())
            .arg(QKeySequence(Qt::Key_Escape).toString())
        );

        m_ui->m_selection_widget->setAlignment(Qt::AlignCenter);
        set_pixmap(__p);
    }

    QRect Selection::get_pixmap_rect() const
    {
        QRect ret = get_pixmap().rect();

        ret.moveTopLeft(
            QPoint((width() - ret.width()) / 2, (height() - ret.height()) / 2)
        );

        return ret;
    }

    void Selection::keyPressEvent(QKeyEvent* __e)
    {
        QRect pixmap_rect = get_pixmap_rect();

        switch (__e->key()) {
            case Qt::Key_Enter:
            case Qt::Key_Return:
                if (m_rubber_band.isVisible()) {
                    set_selection(
                        QRect(
                            m_rubber_band.x() - pixmap_rect.x(),
                            m_rubber_band.y() - pixmap_rect.y(),
                            m_rubber_band.width(),
                            m_rubber_band.height()
                        )
                    );
                }

                break;
            case Qt::Key_Escape:
                reset_selection();

                break;
            default:
                QWidget::keyPressEvent(__e);

                break;
        }
    }

    void Selection::mousePressEvent(QMouseEvent* __e)
    {
        QPoint origin = __e->pos();

        setFocus();

        if (get_pixmap_rect().contains(origin)) {
            m_rubber_band.setGeometry(
                QRect(m_origin = std::move(origin), QSize())
            );

            m_rubber_band.show();
        }

        QWidget::mousePressEvent(__e);
    }

    void Selection::mouseMoveEvent(QMouseEvent* __e)
    {
        QPoint bottom_right = __e->pos();

        if (get_pixmap_rect().contains(bottom_right)) {
            m_rubber_band.setGeometry(
                QRect(m_origin, std::move(bottom_right)).normalized()
            );
        }

        QWidget::mouseMoveEvent(__e);
    }

    void Selection::resizeEvent(QResizeEvent* __e)
    {
        reset_selection();

        QWidget::resizeEvent(__e);
    }

    void Selection::set_selection(QRect __s) noexcept
    {
        m_selection = std::move(__s);

        emit selection_changed(m_selection);
    }

    void Selection::reset_selection() noexcept
    {
        set_selection(QRect());
        m_rubber_band.hide();
    }
}

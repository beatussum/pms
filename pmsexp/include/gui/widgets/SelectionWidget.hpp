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


#ifndef PMSEXP_GUI_WIDGETS_SELECTION_WIDGET_HPP
#define PMSEXP_GUI_WIDGETS_SELECTION_WIDGET_HPP

#include "core/core.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QRubberBand>

namespace gui::widgets
{
    class SelectionWidget : public QLabel
    {
        Q_OBJECT

        Q_PROPERTY(
            QRect selection
            READ get_selection
            WRITE set_selection
            RESET reset_selection
            NOTIFY selection_changed
        )

    public:
        explicit SelectionWidget(
            const QPixmap&,
            QWidget* __parent = nullptr,
            Qt::WindowFlags   = {}
        );

        explicit SelectionWidget(
            const cv::Mat& __m,
            QWidget* __parent   = nullptr,
            Qt::WindowFlags __f = {}
        )
            : SelectionWidget(qpixmap_from_mat(__m), __parent, __f)
        {}

        explicit SelectionWidget(
            QWidget* __parent   = nullptr,
            Qt::WindowFlags __f = {}
        )
            : SelectionWidget(QPixmap(), __parent, __f)
        {}
    private:
        void __update_rubber_band_geometry();
    protected:
        void keyPressEvent(QKeyEvent*) override;
        void mousePressEvent(QMouseEvent*) override;
        void mouseMoveEvent(QMouseEvent*) override;
        void resizeEvent(QResizeEvent*) override;
        void showEvent(QShowEvent*) override;
    signals:
        void selection_changed(const QRect& __new_selection);
    public slots:
        void setPixmap(const QPixmap& __p) { QLabel::setPixmap(__p); }

        void setPixmap(const cv::Mat& __m)
            { setPixmap(qpixmap_from_mat(__m)); }
    public:
        QRect get_pixmap_rect() const;

        QRect get_selection() const noexcept { return m_selection; }
        bool has_selection() const noexcept { return m_selected; }
        void set_selection(QRect) noexcept;
        void reset_selection() noexcept;
    private:
        QPoint      m_origin;
        QRubberBand m_rubber_band;
        bool        m_selected;
        QRect       m_selection;
    };
}

#endif // PMSEXP_GUI_WIDGETS_SELECTION_WIDGET_HPP

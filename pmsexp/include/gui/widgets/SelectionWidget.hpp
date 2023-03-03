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

#include <opencv2/core/mat.hpp>

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
            : SelectionWidget(
                QPixmap::fromImage(
                    QImage(
                        static_cast<const uchar*>(__m.data),
                        __m.cols,
                        __m.rows,
                        QImage::Format_RGB888
                    )
                ),

                __parent,
                __f
            )
        {}

        explicit SelectionWidget(
            QWidget* __parent   = nullptr,
            Qt::WindowFlags __f = {}
        )
            : SelectionWidget(QPixmap(), __parent, __f)
        {}
    public:
        QRect get_selection() const noexcept { return m_selection; }
        bool has_selection() const noexcept { return m_selection.isEmpty(); }
    protected:
        virtual void keyPressEvent(QKeyEvent*) override;
        virtual void mousePressEvent(QMouseEvent*) override;
        virtual void mouseMoveEvent(QMouseEvent*) override;
        virtual void mouseReleaseEvent(QMouseEvent*) override;
    signals:
        void selection_changed(const QRect& __new_selection);
    public slots:
        void set_selection(QRect) noexcept;
        void reset_selection() noexcept { set_selection(QRect()); }
    private:
        QPoint      m_origin;
        QRubberBand m_rubber_band;
        QRect       m_selection;
    };
}

#endif // PMSEXP_GUI_WIDGETS_SELECTION_WIDGET_HPP

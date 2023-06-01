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


#include "gui/widgets/pages/statistics/Trajectory.hpp"

#include <QtGui/QPainter>

namespace gui::widgets::pages::statistics
{
    void draw_full_positions(
        QPainter& __p,
        const QColor& __c,
        const full_positions_type& __f,
        double __ratio = 1.
    )
    {
        __p.setPen(__c);

        for (auto [angle, pos] : __f) {
            pos /= __ratio;

            __p.drawEllipse(pos.x, pos.y, 4, 4);
        }
    }

    Trajectory::Trajectory(
        const std::array<full_positions_type, 2>& __comp_data,
        const full_positions_type& __ex_data,
        double __ratio,
        const cv::Size& __size,
        QWidget* __parent,
        Qt::WindowFlags __f
    )
        : QWidget(__parent, __f)
        , m_ui(new Ui::Trajectory())
    {
        m_ui->setupUi(this);

        m_ui->m_legend_label->setText(
            tr(
                "<font color=\"%1\">Positions calculées</font><br>"
                "<font color=\"%2\">Positions expérimentales</font><br>"
                "<font color=\"%3\">Positions cibles</font>"
            )
                .arg(computed_data_color.name())
                .arg(ex_data_color.name())
                .arg(target_data_color.name())
        );

        set_data(__comp_data, __ex_data, __ratio, __size);
    }

    void Trajectory::set_data(
        const std::array<full_positions_type, 2>& __comp_data,
        const full_positions_type& __ex_data,
        double __ratio,
        const cv::Size& __size
    ) const
    {
        QPixmap pixmap(__size.width, __size.height);

        if (!pixmap.isNull()) {
            QPainter painter(&pixmap);

            reset_data();
            pixmap.fill();

            draw_full_positions(
                painter,
                computed_data_color,
                __comp_data[0],
                __ratio
            );

            draw_full_positions(
                painter,
                target_data_color,
                __comp_data[1],
                __ratio
            );

            draw_full_positions(painter, ex_data_color, __ex_data);

            painter.end();

            m_ui->m_pixmap_label->setPixmap(pixmap);
        }
    }
}

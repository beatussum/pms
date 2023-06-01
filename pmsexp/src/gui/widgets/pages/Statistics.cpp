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


#include "gui/widgets/pages/Statistics.hpp"

#include "gui/widgets/pages/statistics/Trajectory.hpp"

#include <qcustomplot.h>

namespace gui::widgets::pages
{
    Statistics::Statistics(QWidget* __parent, Qt::WindowFlags __f)
        : ListSelecterWidget(__parent, __f)

        , m_trajectory(new statistics::Trajectory(this))
        , m_angular_difference(new QCustomPlot(this))
        , m_spatial_difference(new QCustomPlot(this))
    {
        add_page(
            QIcon::fromTheme("applications-science"),
            tr("Trajectoire"),
            m_trajectory
        );

        add_page(
            QIcon::fromTheme("applications-science"),
            tr("Écart en postion angulaire"),
            m_angular_difference
        );

        add_page(
            QIcon::fromTheme("applications-science"),
            tr("Écart en position spatiale"),
            m_spatial_difference
        );
    }

    void Statistics::set_data(
        std::array<full_positions_type, 2> __comp_data,
        full_positions_type __ex_data,
        double __ratio,
        const cv::Size& __size
    ) const
    {
        reset_data();
        m_trajectory->set_data(__comp_data, __ex_data, __ratio, __size);
    }

    void Statistics::reset_data() const
    {
        m_trajectory->reset_data();
    }
}

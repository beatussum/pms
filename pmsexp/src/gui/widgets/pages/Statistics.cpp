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

#include <qcustomplot.h>

namespace gui::widgets::pages
{
    Statistics::Statistics(QWidget* __parent, Qt::WindowFlags __f)
        : ListSelecterWidget(__parent, __f)
        , m_trajectory(new QCustomPlot())
        , m_angular_difference(new QCustomPlot())
        , m_spatial_difference(new QCustomPlot())
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

    Statistics::~Statistics()
    {
        delete m_trajectory;
        delete m_angular_difference;
        delete m_spatial_difference;
    }
}

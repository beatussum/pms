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


#include "core/core.hpp"

#include <opencv2/core/mat.hpp>
#include <QtGui/QPixmap>

QPixmap qpixmap_from_mat(const cv::Mat& __m)
{
    return QPixmap::fromImage(
        QImage(
            static_cast<const uchar*>(__m.data),
            __m.cols,
            __m.rows,
            QImage::Format_BGR888
        )
    );
}

QPolygon qpolygon_from_contour(contour_type __c)
{
    QVector<QPoint> vec;

    for (const cv::Point& p : __c) {
        vec.push_back(QPoint(p.x, p.y));
    }

    return vec;
}

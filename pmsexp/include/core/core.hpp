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


#ifndef PMSEXP_CORE_CORE_HPP
#define PMSEXP_CORE_CORE_HPP

#include <opencv2/core/types.hpp>
#include <QtCore/QRect>
#include <vector>

class QPixmap;
class QPolygon;

using contour_type  = std::vector<cv::Point>;
using contours_type = std::vector<contour_type>;

QPixmap qpixmap_from_mat(const cv::Mat&);
QPolygon qpolygon_from_contour(contour_type);

inline cv::Rect rect_from_qrect(const QRect& __r)
    { return cv::Rect(__r.x(), __r.y(), __r.width(), __r.height()); }

#endif // PMSEXP_CORE_CORE_HPP

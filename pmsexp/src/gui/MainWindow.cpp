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


#include "gui/MainWindow.hpp"

#include "gui/widgets/SelectionWidget.hpp"
#include "gui/widgets/pages/ContourSelection.hpp"
#include "gui/widgets/pages/Selection.hpp"
#include "gui/widgets/pages/Statistics.hpp"
#include "gui/widgets/pages/Upload.hpp"

#include <opencv2/imgproc.hpp>

namespace gui
{
    MainWindow::MainWindow(QWidget* __parent, Qt::WindowFlags __f)
        : QMainWindow(__parent, __f)

        , m_capture()
        , m_first_frame()
        , m_ui(new Ui::MainWindow())

        , m_contour_selection_page(new widgets::pages::ContourSelection())
        , m_selection_page(new widgets::pages::Selection())
        , m_statistics_page(new widgets::pages::Statistics())
        , m_upload_page(new widgets::pages::Upload())
    {
        m_ui->setupUi(this);

        m_ui->m_central_widget->add_page(m_upload_page);
        m_ui->m_central_widget->add_page(m_selection_page);
        m_ui->m_central_widget->add_page(m_contour_selection_page);
        m_ui->m_central_widget->add_page(m_statistics_page);

        QObject::connect(
            m_upload_page,
            &widgets::pages::Upload::upload_status_changed,
            this,
            &MainWindow::load_selection
        );

        QObject::connect(
            m_selection_page->get_selection_widget(),
            &widgets::SelectionWidget::selection_changed,
            this,
            &MainWindow::find_contours
        );

        QObject::connect(
            m_ui->m_action_reset,
            &QAction::triggered,
            this,
            &MainWindow::reset
        );
    }

    MainWindow::~MainWindow()
    {
        delete m_ui;

        delete m_contour_selection_page;
        delete m_selection_page;
        delete m_statistics_page;
        delete m_upload_page;
    }

    void MainWindow::find_contours(const QRect& __new_selection)
    {
        if (__new_selection.isEmpty()) {
            m_ui->m_central_widget->set_progress(1);
        } else {
            cv::Mat       binary_frame;
            contours_type contours, new_contours;

            cv::Rect roi     = rect_from_qrect(__new_selection);
            double  roi_area = roi.area();

            cv::Mat split_first_frame[3];

            cv::split(cv::Mat(m_first_frame, roi), split_first_frame);

            cv::threshold(
                std::move(split_first_frame[2]),
                binary_frame,
                -1.,
                255.,
                cv::THRESH_BINARY | cv::THRESH_OTSU
            );

            cv::findContours(
                std::move(binary_frame),
                contours,
                cv::RETR_LIST,
                cv::CHAIN_APPROX_NONE,
                roi.tl()
            );

            for (auto i = contours.begin(); i != contours.end(); ++i) {
                double contour_area = cv::contourArea(*i);

                if (std::abs((contour_area - roi_area) / roi_area) < .8) {
                    new_contours.push_back(std::move(*i));
                }
            }

            if (std::size_t size = new_contours.size(); size == 0) {
                m_ui->m_central_widget->set_progress(1);

                m_ui->m_status_bar->showMessage(
                    tr("Aucun contour trouvé."), 2'000
                );
            } else {
                m_contour_selection_page->set_contours(
                    std::move(new_contours),
                    m_first_frame
                );

                m_ui->m_central_widget->set_progress(3);

                m_ui->m_status_bar->showMessage(
                    tr("%n contour(s) trouvé(s).", nullptr, size), 2'000
                );
            }
        }
    }

    void MainWindow::load_selection()
    {
        if (m_upload_page->is_upload_valid()) {
            QString file_path = m_upload_page->get_ex_file_path();

            if (m_capture.open(file_path.toStdString())) {
                if (m_capture.read(m_first_frame)) {
                    m_selection_page->get_selection_widget()->setPixmap(
                        m_first_frame
                    );

                    m_ui->m_central_widget->set_progress(1);
                } else {
                    m_ui->m_status_bar->showMessage(
                        tr("Aucun « frame » n'a pu ếtre récupéré."),
                        2'000
                    );
                }
            } else {
                m_ui->m_status_bar->showMessage(
                    tr("Erreur lors de l'ouverture du fichier « %1 ».")
                        .arg(file_path),

                    2'000
                );
            }
        } else {
            m_ui->m_central_widget->set_progress(0);
        }
    }

    void MainWindow::reset()
    {
        m_contour_selection_page->reset_contours();
        m_selection_page->get_selection_widget()->reset_selection();
        m_upload_page->reset_upload_status();
    }
}

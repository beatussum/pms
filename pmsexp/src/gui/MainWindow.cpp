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

#include <opencv2/tracking.hpp>

#include <QtConcurrent/QtConcurrent>
#include <QtWidgets/QProgressBar>

namespace gui
{
    MainWindow::MainWindow(QWidget* __parent, Qt::WindowFlags __f)
        : QMainWindow(__parent, __f)

        , m_capture()
        , m_first_frame()
        , m_future_watcher(this)
        , m_tracker()
        , m_progress_bar(new QProgressBar())
        , m_ui(new Ui::MainWindow())

        , m_contour_selection_page(new widgets::pages::ContourSelection())
        , m_selection_page(new widgets::pages::Selection())
        , m_statistics_page(new widgets::pages::Statistics())
        , m_upload_page(new widgets::pages::Upload())
    {
        m_ui->setupUi(this);

        m_progress_bar->hide();

        m_ui->m_status_bar->addWidget(m_progress_bar);

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
            m_ui->m_central_widget,
            &widgets::ButtonSelecterWidget::run,
            this,
            &MainWindow::run
        );

        QObject::connect(
            m_ui->m_action_reset,
            &QAction::triggered,
            this,
            &MainWindow::reset
        );

        QObject::connect(
            &m_future_watcher,
            &QFutureWatcher<full_positions_type>::finished,
            this,
            &MainWindow::show_results
        );

        QObject::connect(
            &m_future_watcher,
            &QFutureWatcher<full_positions_type>::progressValueChanged,
            m_progress_bar,
            &QProgressBar::setValue
        );
    }

    full_positions_type MainWindow::process()
    {
        full_positions_type ret;

        ret.reserve(m_capture.get(cv::CAP_PROP_FRAME_COUNT));

        ret.push_back(
            full_position_from_contour(m_contour_selection_page->get_current())
        );

        int progress = 1;

        emit m_future_watcher.progressValueChanged(progress);

        double current_area = m_contour_selection_page->get_current_area();
        cv::Mat frame;

        cv::Rect roi = rect_from_qrect(
            m_selection_page->get_selection_widget()->get_selection()
        );

        m_capture.set(cv::CAP_PROP_POS_FRAMES, 1.);

        while (m_capture.read(frame)) {
            m_tracker->update(frame, roi);

            ret.push_back(
                full_position_from_contour(
                    *contours_from_mat(frame, roi, current_area).begin()
                )
            );

            emit m_future_watcher.progressValueChanged(++progress);
        }

        return ret;
    }

    void MainWindow::find_contours(const QRect& __new_selection)
    {
        if (__new_selection.isEmpty()) {
            m_ui->m_central_widget->set_progress(1);
        } else {
            sorted_contours_type contours = contours_from_mat(
                m_first_frame,
                rect_from_qrect(__new_selection)
            );

            if (std::size_t size = contours.size(); size == 0) {
                m_ui->m_central_widget->set_progress(1);

                m_ui->m_status_bar->showMessage(
                    tr("Aucun contour trouvé."), 2'000
                );
            } else {
                m_contour_selection_page->set_contours(
                    std::move(contours),
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
                m_capture.set(cv::CAP_PROP_POS_FRAMES, 0.);

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

    void MainWindow::run()
    {
        m_tracker = cv::TrackerKCF::create();

        m_tracker->init(
            m_first_frame,

            rect_from_qrect(
                m_selection_page->get_selection_widget()->get_selection()
            )
        );

        m_ui->m_action_reset->setEnabled(false);
        m_ui->m_central_widget->setEnabled(false);

        m_progress_bar->reset();
        m_progress_bar->setRange(0, m_capture.get(cv::CAP_PROP_FRAME_COUNT));
        m_progress_bar->show();

        m_future_watcher.setFuture(
            QtConcurrent::run(this, &MainWindow::process)
        );
    }

    void MainWindow::show_results()
    {
        m_ui->m_action_reset->setEnabled(true);
        m_ui->m_central_widget->setEnabled(true);

        m_progress_bar->hide();

        m_ui->m_status_bar->showMessage(tr("Terminé !"), 2'000);
    }
}

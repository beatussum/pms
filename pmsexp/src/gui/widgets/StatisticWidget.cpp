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


#include "gui/widgets/StatisticWidget.hpp"

#include "gui/widgets/SelecterWidgetItem.hpp"

namespace gui::widgets
{
    StatisticWidget::StatisticWidget(QWidget* __parent, Qt::WindowFlags __f)
        : QWidget(__parent, __f)
        , m_ui(new Ui::StatisticWidget())
    {
        m_ui->setupUi(this);

        for (auto [icon, txt] : categories) {
            new SelecterWidgetItem(
                std::move(icon), std::move(txt), m_ui->m_selecter
            );
        }

        QObject::connect(
            m_ui->m_selecter,
            &QListWidget::currentRowChanged,
            m_ui->m_stacked_widget,
            &QStackedWidget::setCurrentIndex
        );

        QObject::connect(
            m_ui->m_selecter,
            &QListWidget::currentRowChanged,
            this,
            &StatisticWidget::page_index_changed
        );

        QObject::connect(
            m_ui->m_scroll_down_button,
            &QToolButton::clicked,
            this,
            &StatisticWidget::scroll_down
        );

        QObject::connect(
            m_ui->m_scroll_up_button,
            &QToolButton::clicked,
            this,
            &StatisticWidget::scroll_up
        );

        QObject::connect(
            m_ui->m_selecter,
            &QListWidget::currentRowChanged,
            this,
            &StatisticWidget::__update_scroll_buttons
        );

        m_ui->m_selecter->setCurrentRow(0);
    }

    void StatisticWidget::scroll_down()
    {
        QListWidget* selecter = m_ui->m_selecter;

        selecter->setCurrentRow(
            std::min(selecter->count() - 1, selecter->currentRow() + 1)
        );
    }

    void StatisticWidget::scroll_up()
    {
        QListWidget* selecter = m_ui->m_selecter;

        selecter->setCurrentRow(std::max(0, selecter->currentRow() - 1));
    }

    void StatisticWidget::__update_scroll_buttons(int __current_row)
    {
        m_ui->m_scroll_down_button->setDisabled(
            __current_row == (m_ui->m_selecter->count() - 1)
        );

        m_ui->m_scroll_up_button->setDisabled(__current_row == 0);
    }
}

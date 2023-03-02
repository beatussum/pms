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


#ifndef PMSEXP_GUI_STATISTIC_WIDGET_HPP
#define PMSEXP_GUI_STATISTIC_WIDGET_HPP

#include "ui_StatisticWidget.h"

namespace gui
{
    class StatisticWidget : public QWidget
    {
        Q_OBJECT

        Q_PROPERTY(
            int page_index
            READ get_page_index
            WRITE set_page_index
            NOTIFY page_index_changed
            STORED false
        )

    public:
        using category_type   = std::pair<QIcon, QString>;
        using categories_type = std::array<category_type, 3>;
    public:
        inline static const categories_type categories = {
            std::make_pair(
                QIcon::fromTheme("applications-science"),
                "Trajectoire"
            ),

            std::make_pair(
                QIcon::fromTheme("applications-science"),
                "Écart en position"
            ),

            std::make_pair(
                QIcon::fromTheme("applications-science"),
                "Écart en position angulaire"
            )
        };
    public:
        explicit StatisticWidget(
            QWidget* __parent = nullptr,
            Qt::WindowFlags   = {}
        );

        virtual ~StatisticWidget() { delete m_ui; }
    public:
        int get_page_index() const { return m_ui->m_selecter->currentRow(); }
        void set_page_index(int __i) { m_ui->m_selecter->setCurrentRow(__i); }
    signals:
        void page_index_changed(int __current_index);
    public slots:
        void scroll_down();
        void scroll_up();
    private slots:
        void __update_scroll_buttons(int __current_row);
    private:
        Ui::StatisticWidget* m_ui;
    };
}

#endif // PMSEXP_GUI_STATISTIC_WIDGET_HPP

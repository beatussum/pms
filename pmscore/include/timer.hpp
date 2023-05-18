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


#ifndef PMSCORE_TIMER_HPP
#define PMSCORE_TIMER_HPP

#include "core/macros.hpp"
#include "core/utility.hpp"

#include <stdint.h>

/**
 * @file
 *
 * @brief Ce fichier implémente un minuteur.
 */

namespace pmscore
{
    /**
     * @brief Cette interface permet l'implémentation d'un _« callback »_.
     *
     * La raison d'être de cette classe est de permettre du _« type erasure »_.
     */

    class callback_base
    {
    public:
        /**
         * @brief Surcharge de l'opérateur `operator()`.
         *
         * Cette méthode s'occupe d'appeler le _« callback »_.
         */

        virtual void operator()() = 0;
    };

    template <class _T>
    class callback final : public callback_base
    {
    public:
        using callback_type = _T;
    public:
        callback(_T&& __callback) noexcept_pf(_T)
            : m_callback(forward<_T>(__callback))
        {}
    public:
        void operator()() override { m_callback(); }
    private:
        callback_type m_callback;
    };

    class timer
    {
    public:
        /**
         * @brief Construit un objet `timer`.
         *
         * @warning Ce constructeur par défaut crée un objet `timer` invalide :
         * si l'appel de ce constructeur est directement suivi par celui de la
         * méthode `update_status()`, le programme se termine d'une manière non
         * prévue.
         */

        constexpr timer()
            : m_callback(nullptr)
            , m_delay(0)
            , m_time(0)
        {}

        /**
         * @brief Construit un objet `timer`.
         *
         * @tparam _T Le type du _« callback »_.
         * @param __callback Le _« callback »_.
         * @param __delay La période d'appel du _« callback »_.
         */

        template <class _T>
        explicit timer(_T&& __callback, uint32_t __delay)
            : m_callback(new callback(forward<_T>(__callback)))
            , m_delay(__delay)
            , m_time(0)
        {}
    public:
        callback_base* get_callback() const noexcept { return m_callback; }

        template <class _T>
        void set_callback(_T&&);

        uint32_t get_delay() const noexcept { return m_delay; }
        void set_delay(uint32_t __d) noexcept { m_delay = __d; }
    public:
        /**
         * @brief Actualise le statut de l'objet.
         *
         * Actualise l'horloge interne stockée dans l'objet et appel, si
         * nécessaire, le _« callback »_.
         */

        void update_status();
    private:
        callback_base* m_callback;
        uint32_t       m_delay;

        uint32_t m_time;
    };
}

#include "timer.ipp"

#endif // PMSCORE_TIMER_HPP

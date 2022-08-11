/*
 * Copyright (C) 2022 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
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


#ifndef PMSCORE_ARDUINO_ENCODER_HPP
#define PMSCORE_ARDUINO_ENCODER_HPP

#include "arduino/arduino.hpp"

#include <stddef.h>

namespace pmscore::arduino
{
    class encoder
    {
        friend void set_main_encoders(encoder*, encoder*) noexcept;

        template <size_t>
        friend void update_main_encoder_status() noexcept;
    public:
        static constexpr real incrementation_counts = 1124.4288;
    public:
        explicit encoder(pin_t __pin);
    public:
        pin_t get_pin() const noexcept { return m_pin; }
        real get_angle() const noexcept;
        real get_incrementation() const noexcept { return m_incrementation; }
        bool is_reverse() const noexcept { return m_reverse; }

        void reverse() noexcept { m_reverse = !m_reverse; }
    private:
        pin_t m_pin;

        volatile real m_incrementation;
        bool          m_reverse;
    };
}

#endif // PMSCORE_ARDUINO_ENCODER_HPP

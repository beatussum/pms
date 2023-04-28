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


#ifndef PMSCORE_ARDUINO_ULTRASONIC_SENSOR_HPP
#define PMSCORE_ARDUINO_ULTRASONIC_SENSOR_HPP

#include "arduino/arduino.hpp"

#include <Arduino.h>

namespace pmscore::arduino
{
    class ultrasonic_sensor
    {
        friend void update_main_ultrasonic_sensor_status();
    public:
        static constexpr real speed_of_sound = 3.40e-2;
    public:
        explicit ultrasonic_sensor(pin_t __pin_echo, pin_t __pin_trig);
    public:
        void start_echoing();
        void stop_echoing() const { digitalWrite(m_pin_echo, LOW); }
    public:
        pin_t get_pin_echo() const noexcept { return m_pin_echo; }
        void set_pin_echo(pin_t __p) { pinMode(m_pin_echo = __p, OUTPUT); }

        pin_t get_pin_trig() const noexcept { return m_pin_trig; }
        void set_pin_trig(pin_t __p) { pinMode(m_pin_trig = __p, OUTPUT); }

        real get_distance() const noexcept
            { return static_cast<real>(m_duration) * (speed_of_sound / 2); }

        real get_duration() const noexcept { return m_duration; }

        bool is_echoing() const
            { return (read_digital_output(m_pin_echo) == HIGH); }
    private:
        pin_t m_pin_echo;
        pin_t m_pin_trig;

        volatile uint32_t m_duration;
    };

    inline ultrasonic_sensor* main_ultrasonic_sensor = nullptr;

    void set_main_ultrasonic_sensor(ultrasonic_sensor*);
    void update_main_ultrasonic_sensor_status();
}

#endif // PMSCORE_ARDUINO_ULTRASONIC_SENSOR_HPP

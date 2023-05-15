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


#include "arduino/ultrasonic_sensor.hpp"

namespace pmscore::arduino
{
    ultrasonic_sensor::ultrasonic_sensor(pin_t __pin_echo, pin_t __pin_trig)
        : m_pin_echo(__pin_echo)
        , m_pin_trig(__pin_trig)
        , m_duration(0)
    {
        pinMode(m_pin_echo, OUTPUT);
        pinMode(m_pin_trig, OUTPUT);
    }

    void ultrasonic_sensor::start_echoing()
    {
        m_duration = UINT32_MAX;

        digitalWrite(m_pin_echo, HIGH);
    }

    void set_main_ultrasonic_sensor(ultrasonic_sensor* __us)
    {
        if (main_ultrasonic_sensor != nullptr) {
            detachInterrupt(
                digitalPinToInterrupt(main_ultrasonic_sensor->get_pin_trig())
            );
        }

        main_ultrasonic_sensor = __us;

        attachInterrupt(
            digitalPinToInterrupt(main_ultrasonic_sensor->get_pin_trig()),
            &update_main_ultrasonic_sensor_status,
            CHANGE
        );
    }

    void update_main_ultrasonic_sensor_status()
    {
        if (main_ultrasonic_sensor->is_echoing()) {
            if (main_ultrasonic_sensor->m_duration == UINT32_MAX) {
                main_ultrasonic_sensor->m_duration = micros();
            } else {
                main_ultrasonic_sensor->m_duration =
                    micros() - main_ultrasonic_sensor->m_duration;

                main_ultrasonic_sensor->stop_echoing();
            }
        }
    }
}

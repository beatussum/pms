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


#include "arduino/chopper.hpp"
#include "arduino/encoder.hpp"
#include "arduino/encoders.hpp"
#include "arduino/motoreductor.hpp"
#include "speed_profile/constant.hpp"
#include "speed_profile/trapezoidal.hpp"
#include "correcter.hpp"
#include "position_computer.hpp"

using namespace pmscore;

arduino::chopper chopper(8);

arduino::encoder encoder_a(2);
arduino::encoder encoder_b(3);

arduino::motoreductor motor_a(10, 9, 11, &encoder_a);
arduino::motoreductor motor_b(6, 7, 5, &encoder_b);

correcter corr(
    &motor_a,
    &motor_b,
    speed_profile::trapezoidal(10., .01, 10, 0, 20, &angle_distance),
    speed_profile::constant(.01, 100, &angle_distance),

    speed_profile::trapezoidal(2., 20., 100, 90, 180,
        [] (real __a, real __b) { return __b - __a; }
    )

);

position_computer computer(
    &corr,
    .2,
    {{0., 1'000.}, {-1'000., 0.}, {0., -1'000.}, {1'000., 0.}},
    5.
);

arduino::encoders encoders(&encoder_a, &encoder_b, &computer);

void setup()
{
    Serial.begin(9600);

    arduino::set_main_encoders(encoders);
    chopper.enable();
}

void loop()
{
    encoders.update_status();
}

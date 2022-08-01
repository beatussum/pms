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
#include "speed_profile/triangular.hpp"
#include "correcter.hpp"
#include "position_computer.hpp"

arduino::chopper chopper(6);

arduino::encoder encoder_a(7);
arduino::encoder encoder_b(12);

arduino::motoreductor motor_a(
    4, 5, 3,
    &encoder_a,
    arduino::motoreductor::direction::Front,
    200
);

arduino::motoreductor motor_b(
    10, 11, 9,
    &encoder_b,
    arduino::motoreductor::direction::Front,
    200
);

correcter corr(&motor_a, &motor_b, .1, speed_profile::triangular(2., 200));

position_computer computer(
    &corr,
    .1,
    {{0., 70.}, {-70., 0.}, {0., -70.}, {70., 0.}},
    5.
);

arduino::encoders encoders(&encoder_a, &encoder_b, &computer);

void setup()
{
    Serial.begin(9600);
    chopper.enable();
}

void loop()
{
    encoders.update_status();
}

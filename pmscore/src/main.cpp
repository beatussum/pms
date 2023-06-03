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


#include "arduino/chopper.hpp"
#include "arduino/connecter.hpp"
#include "arduino/encoder.hpp"
#include "arduino/motoreductor.hpp"

#include "json/json_array.hpp"
#include "json/json_live_array.hpp"
#include "json/json_live_object.hpp"
#include "json/json_object.hpp"
#include "json/json_property.hpp"
#include "json/json_value.hpp"

#include "speed_profile/constant.hpp"
#include "speed_profile/trapezoidal.hpp"

#include "correcter.hpp"
#include "position_computer.hpp"

#include <SPI.h>
#include <SD.h>

using namespace pmscore;

arduino::chopper chopper(8);

arduino::encoder encoder_a(2);
arduino::encoder encoder_b(3);

arduino::motoreductor motor_a(10, 9, 11, &encoder_a);
arduino::motoreductor motor_b(6, 7, 5, &encoder_b);

arduino::ultrasonic_sensor usensor(1, 1);

correcter corr(
    &motor_a,
    &motor_b,
    speed_profile::trapezoidal(10., .01, 10, 0, 25, &angle_distance),
    speed_profile::constant(.01, 100, &angle_distance),

    speed_profile::trapezoidal(2., 20., 100, 90, 180,
        [] (real __a, real __b) { return __b - __a; }
    ),

    15
);

vector path[] = {{0., 1'000.}, {-1'000., 0.}, {0., -1'000.}, {1'000., 0.}};

position_computer computer(.2, path, 5.);

arduino::connecter connecter(
    &encoder_a,
    &encoder_b,
    &usensor,
    500,
    &computer,
    corr
);

File file;

json::json_live_array json_data(&file);
json::json_live_object json_main_object(&file);

void operator delete(void* __ptr, size_t __size)
{
    free(__ptr);
}

void operator delete[](void* __ptr, size_t __size)
{
    free(__ptr);
}

void setup()
{
    Serial.begin(9'600);
    pinMode(SS, OUTPUT);

    Serial.print("Initialisation");

    while (!SD.begin(SPI_HALF_SPEED, 53)) {
        Serial.print('.');
    }

    Serial.println();

    file = SD.open("comp_data.json", FILE_WRITE);

    if (!file) {
        Serial.println("Cannot open `comp_data.json`.");
    }

    json::json_array json_path;

    for (const vector& v : path) {
        json_path.push_back(static_cast<json::json_object>(v));
    }

    file.print(", \"data\": ");

    arduino::set_main_encoders(&encoder_a, &encoder_b);
    arduino::set_main_ultrasonic_sensor(&usensor);

    chopper.enable();
}

void loop()
{
    if (!computer.is_ended()) {
        json_data.push_back(static_cast<json::json_object>(computer));
    } else if (!json_main_object.is_ended()) {
        json_main_object.serialize();
    }

    connecter.update_status();
}

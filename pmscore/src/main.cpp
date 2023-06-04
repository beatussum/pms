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
#include "arduino/encoder.hpp"
#include "arduino/encoders.hpp"
#include "arduino/motoreductor.hpp"

#include "speed_profile/constant.hpp"
#include "speed_profile/trapezoidal.hpp"

#include "correcter.hpp"
#include "position_computer.hpp"

#include <SPI.h>
#include <SD.h>

using namespace pmscore;

arduino::chopper chopper(8);

arduino::encoder encoder_a(3);
arduino::encoder encoder_b(2);

arduino::motoreductor motor_a(6, 7, 5, &encoder_a);
arduino::motoreductor motor_b(9, 10, 11, &encoder_b);

correcter corr(
    &motor_a,
    &motor_b,
    speed_profile::trapezoidal(10., .001, 30, 0, 30, &angle_distance),
    speed_profile::constant(.01, 55, &angle_distance),

    speed_profile::trapezoidal(2., 20., 80, 55, 80,
        [] (real __a, real __b) { return __b - __a; }
    )

);

vector path[] = {{0., 100.}, {0., -100.}};

position_computer computer(&corr, .8, path, 5., false);
arduino::encoders encoders(&encoder_a, &encoder_b, &computer);

File file;
bool is_json_ended = false;

void setup()
{
    Serial.begin(9'600);
    pinMode(SS, OUTPUT);

    Serial.print("Initialisation");
    while (!SD.begin(SPI_HALF_SPEED, 53)) { Serial.print('.'); }
    Serial.println();

    file = SD.open("COMP", FILE_WRITE);

    if (!file) {
        Serial.println("Cannot open `COMP`.");
    }

    String order = "{ ";

    for (auto i = begin(path); i != (end(path) - 1); ++i) {
        order += (i->to_json() + ", ");
    }

    order += (end(path)[-1].to_json() + " }");

    file.print(
        "{\n"
        "\t\"order\": " + move(order) + ",\n\n"
        "\t\"data\": [\n"
        "\t\t" + computer.to_json()
    );

    file.flush();

    arduino::set_main_encoders(encoders);

    chopper.enable();
}

void loop()
{
    if (!computer.is_ended()) {
        file.print(
            ",\n"
            "\t\t" + computer.to_json()
        );

        file.flush();

        // Serial.println(static_cast<String>(computer));

        encoders.update_status();
    } else if (!is_json_ended) {
        is_json_ended = true;

        file.print(
            ",\n"
            "\t\t" + computer.to_json() + "\n"
            "\t]\n"
            "}\n"
        );

        file.close();
    }
}

/*
 * Copyright (C) 2022 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
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


#include "src/arduino/chopper.hpp"
#include "src/arduino/encoder.hpp"
#include "src/arduino/motoreductor.hpp"
#include "src/path/path_computer.hpp"
#include "src/path/position_computer.hpp"
#include "src/correcter.hpp"

arduino::motoreductor ma(
    4, 5, 3,
    arduino::motoreductor::direction::Front,
    170
);


arduino::motoreductor mb(
    10, 11, 9,
    arduino::motoreductor::direction::Front,
    170
);

arduino::encoder enca(7);
arduino::encoder encb(12);
arduino::chopper ch(6);

path::path_computer<4> pac(
    { vector(0., 70.), vector(-70., 0.), vector(0., -70.), vector(70., 0.) },
    &enca,
    &encb
);

path::position_computer pos(&enca, &encb);

correcter corr(&pac, &pos, &ma, &mb, 0.05);

using namespace core;

void setup()
{
    Serial.begin(9600);
    ch.enable();
}

void loop()
{
    corr();
}

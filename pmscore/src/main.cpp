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


#include "arduino/chopper.hpp"
#include "arduino/encoder.hpp"
#include "arduino/encoders.hpp"
#include "arduino/motoreductor.hpp"
#include "position/computers.hpp"
#include "position/real_computer.hpp"
#include "position/theoretical_computer.hpp"
#include "correcter.hpp"

arduino::chopper ch(6);

arduino::encoder enca(7);
arduino::encoder encb(12);

arduino::motoreductor ma(
    4, 5, 3,
    &enca,
    arduino::motoreductor::direction::Front,
    200
);

arduino::motoreductor mb(
    10, 11, 9,
    &encb,
    arduino::motoreductor::direction::Front,
    200
);

position::real_computer rcomputer;

position::theoretical_computer tcomputer(
    {{0., 70.}, {-70., 0.}, {0., -70.}, {70., 0.}}
);

correcter corr(&ma, &mb, 0.05);

position::computers computers(&rcomputer, &tcomputer, &corr);
arduino::encoders encoders(&enca, &encb, &computers);

void setup()
{
    Serial.begin(9600);
    ch.enable();
}

void loop()
{
    encoders.update_status();
}

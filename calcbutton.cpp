/*
 *  Basicalc - Simple Qt Calculator
 *  Copyright (C) 2023	Bonevelous
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "calcbutton.h"

CalcButton::CalcButton(QWidget *parent) : QPushButton(parent) {
}

CalcButton::~CalcButton() {
}

function CalcButton::b_func() {
	return _b_func;
}

void CalcButton::set_b_func(function n_b_func) {
	_b_func = n_b_func;
}

int CalcButton::num_val() {
	return _num_val;
}

void CalcButton::set_num_val(int n_num_val) {
	_num_val = n_num_val;
}


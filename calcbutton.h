#ifndef CALC_BUTTON_H
#define CALC_BUTTON_H

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

#include <QPushButton>

#include "enums.h"

class CalcButton : public QPushButton {
	public:
		CalcButton(QWidget *parent = nullptr);
		~CalcButton();

		int num_val();
		void set_num_val(int n_num_val);

		function b_func();
		void set_b_func(function n_b_func);

	private:
		int _num_val = 0;
		function _b_func = FUNC_NONE;
};

#endif //CALC_BUTTON_H


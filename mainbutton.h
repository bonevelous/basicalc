#ifndef MAINBUTTON_H
#define MAINBUTTON_H

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

class MainButton : public QPushButton {

	Q_OBJECT

	public:
		MainButton(QWidget *parent = nullptr);
		~MainButton();

	private:
		void button_size_hint();
		void set_button_type(main_button_enum _enum);
		void set_button_val(operation_enum _enum);

	private:
		main_button_enum mbutton_type;
		operation_enum mbutton_val;
};

#endif //MAINBUTTON_H

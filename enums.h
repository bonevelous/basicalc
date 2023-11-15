#ifndef ENUMS_H
#define ENUMS_H

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

typedef enum main_button_enum {
	MAIN_FUNC_NONE,
	MAIN_FUNC_DIGIT,
	MAIN_FUNC_OPERATION,
	MAIN_FUNC_ANSWER,
	MAIN_FUNC_CLEAR
} main_button_enum;

typedef enum operation_enum {
	OPERATION_NONE,
	OPERATION_ADD,
	OPERATION_SUBTRACT,
	OPERATION_MULTIPLY,
	OPERATION_DIVIDE
} operation_enum;

#endif //ENUMS_H

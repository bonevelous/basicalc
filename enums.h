/*******************************************************************************

    Basicalc - Basic QT Calculator
    Copyright (C) 2023	Matthew Gobbi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*******************************************************************************/

#ifndef ENUMS_H
#define ENUMS_H

typedef enum operEnum {
	OPERATION_NONE,
	OPERATION_ERROR,
	OPERATION_ADD,
	OPERATION_SUBTRACT,
	OPERATION_MULTIPLY,
	OPERATION_DIVIDE,
	OPERATION_POWER,
	OPERATION_ROOT,
	OPERATION_MODULUS,
	OPERATION_SIGN_SWAP
} operEnum;

typedef enum memBtnEnum {
	MEMORY_DEFAULT,
	MEMORY_STORE,
	MEMORY_CLEAR,
	MEMORY_RECALL,
	MEMORY_ALT
} memBtnEnum;

#endif //ENUMS_H

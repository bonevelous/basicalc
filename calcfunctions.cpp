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

#include "calcfunctions.h"
//#include <complex>

bool calcInstaAns(operEnum _enum) {
	bool _answer = false;
	switch(_enum) {
		case OPERATION_SIGN_SWAP:
			_answer = true;
			break;
		default:
			break;
	}
	return _answer;
}

void calcAnswer(operEnum *_enum, double gMem, double *oldAns) {
	switch (*_enum) {
		case OPERATION_ADD:
			*oldAns += gMem;
			break;
		case OPERATION_SUBTRACT:
			*oldAns -= gMem;
			break;
		case OPERATION_MULTIPLY:
			*oldAns *= gMem;
			break;
		case OPERATION_DIVIDE:
			if (gMem != 0) {
				*oldAns /= gMem;
			} else {
				*_enum = OPERATION_ERROR;
				*oldAns = 0;
			}
			break;
		case OPERATION_POWER:
			*oldAns = pow(*oldAns, gMem);
			break;
		case OPERATION_ROOT:
			if (gMem >= 0) {
				*oldAns = pow(*oldAns, (1 / gMem));
			} else {
				*_enum = OPERATION_ERROR;
				*oldAns = 0;
			}
			break;
		case OPERATION_MODULUS:
			*oldAns = round(fmod(*oldAns, gMem));
			break;
		case OPERATION_SIGN_SWAP:
			*oldAns = -gMem;
			break;
		default:
			break;
	}
}


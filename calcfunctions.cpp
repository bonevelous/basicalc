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

bool calcInstaAns(operEnum _enum) {
	bool _answer = false;
	switch(_enum) {
		case OPERATION_SIGN_SWAP:
			_answer = true;
			break;
		case OPERATION_FACTORIAL:
			_answer = true;
			break;
		case OPERATION_ABSOLUTE:
			_answer = true;
			break;
		case OPERATION_SIN:
			_answer = true;
			break;
		case OPERATION_COS:
			_answer = true;
			break;
		case OPERATION_TAN:
			_answer = true;
			break;
		case OPERATION_CSC:
			_answer = true;
			break;
		case OPERATION_SEC:
			_answer = true;
			break;
		case OPERATION_COT:
			_answer = true;
			break;
		default:
			break;
	}
	return _answer;
}

void calcAnswer(operEnum *_enum, double gMem, double *oldAns, bool _altMode) {
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
				*oldAns = pow(gMem, (1.0 / *oldAns));
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
		case OPERATION_FACTORIAL:
			{
				int gMemInt = (int) gMem;
				int curAns = gMemInt;
				for (int i = curAns - 1; i > 0; i--) {
					curAns *= i;
				}
				*oldAns = (double) curAns;
			}
			break;
		case OPERATION_ABSOLUTE:
			*oldAns = abs(gMem);
			break;
		case OPERATION_SIN:
			_altMode == true ? *oldAns = asin(gMem) : *oldAns = sin(gMem);
			break;
		case OPERATION_COS:
			_altMode == true ? *oldAns = acos(gMem) : *oldAns = cos(gMem);
			break;
		case OPERATION_TAN:
			_altMode == true ? *oldAns = atan(gMem) : *oldAns = tan(gMem);
			break;
		case OPERATION_CSC:
			_altMode == true ? *oldAns = (1 / asin(gMem)) : *oldAns = (1 / sin(gMem));
			break;
		case OPERATION_SEC:
			_altMode == true ? *oldAns = (1 / acos(gMem)) : *oldAns = (1 / cos(gMem));
			break;
		case OPERATION_COT:
			_altMode == true ? *oldAns = (1 / atan(gMem)) : *oldAns = (1 / tan(gMem));
			break;
		default:
			break;
	}
}


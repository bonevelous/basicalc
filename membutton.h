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

#ifndef MEMBUTTON_H
#define MEMBUTTON_H

#include <QPushButton>
#include "enums.h"

class MemButton : public QPushButton {
	public:
		MemButton(QWidget *parent = nullptr);
		~MemButton();

		memBtnEnum memFunc();
		void setMemFunc(memBtnEnum _memFunc);

	private:
		memBtnEnum m_memFunc;
};

#endif //MEMBUTTON_H

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

#include <QApplication>
#include <iostream>
#include <getopt.h>

#include "mainwindow.h"

static struct option longopt[] = {
	{"help", 0, 0, 'h'},
	{"version", 0, 0, 'v'},
	{0, 0, 0, 0}
};

int main (int argc, char **argv) {

	int index = 0;
	int c= 0;

	c = getopt_long (argc, argv, "hv", longopt, &index);

	switch (c) {
		case 'h':
			std::cout << "Usage: ./basicalc [OPTION]..." << std::endl;
			std::cout << "\t--help\t| -h : This help message" << std::endl;
			std::cout << "\t--version\t| -v : Version Number" << std::endl;
			return 0;
			break;
		case 'v':
			std::cout << VERSION_MAJOR << '.' << VERSION_MINOR << \
				'.' << VERSION_BUILD << std::endl;
			return 0;
			break;
		default:
			break;
	}

	QApplication app (argc, argv);

	MainWindow win;
	win.show();

	return app.exec();
}

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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainButton *testButton;

MainWindow::MainWindow (QWidget *parent) :
	QMainWindow (parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	testButton = MainWindow::findChild<MainButton *>("clsButton");
	connect(testButton, &MainButton::released, this, &MainWindow::test_button);
}

void MainWindow::test_button () {
	QTextStream out(stdout);

	out << "Hello World!" << Qt::endl;
}

MainWindow::~MainWindow() {
	delete ui;
}

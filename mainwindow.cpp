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

QPushButton *cls_button;
MainButton *num_button[10];

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow (parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	for (int i = 0; i < 10; i++) {
		QString curDigit = "digit_button" + QString::number(i);
		num_button[i] = MainWindow::findChild<MainButton *>(curDigit);
		connect(num_button[i], &MainButton::released, this, &MainWindow::add_digit);
		num_button[i]->set_button_val(i);
	}

	cls_button = MainWindow::findChild<QPushButton *>("clsButton");
	connect(cls_button, &QPushButton::released, this, &MainWindow::cls_display);
}

void MainWindow::add_digit() {
	MainButton *button = (MainButton *)sender();
	QTextStream out(stdout);

	out << "Digit " << button->get_button_val() << Qt::endl;
}

void MainWindow::cls_display () {
	QTextStream out(stdout);

	out << "Hello World!" << Qt::endl;
}

MainWindow::~MainWindow() {
	delete ui;
}

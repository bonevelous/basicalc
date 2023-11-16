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
QPushButton *pnt_button;
MainButton *num_button[10];

bool disp_cleared = true;
bool fractional = false;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow (parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	for (int i = 0; i < 10; i++) {
		QString curDigit = "digit_button" + QString::number(i);
		num_button[i] = MainWindow::findChild<MainButton *>(curDigit);
		connect(num_button[i], &MainButton::released, this, &MainWindow::add_digit);
		num_button[i]->set_btn_val(i);
	}

	cls_button = MainWindow::findChild<QPushButton *>("clsButton");
	connect(cls_button, &QPushButton::released, this, &MainWindow::cls_display);

	pnt_button = MainWindow::findChild<QPushButton *>("pointButton");
	connect(pnt_button, &QPushButton::released, this, &MainWindow::add_point);
}

void MainWindow::add_digit() {
	MainButton *_btn = (MainButton *)sender();
	QTextStream out(stdout);

	if (disp_cleared == true) {
		if (_btn->btn_val() > 0) {
			ui->calcDisp->setText(QString::number(_btn->btn_val()));
			disp_cleared = false;
		}
	} else if (ui->calcDisp->text().length() < MAXDIGITS) {
		QString newDisp = ui->calcDisp->text() + QString::number(_btn->btn_val());
		ui->calcDisp->setText(newDisp);
	}
}

void MainWindow::cls_display () {
	QTextStream out(stdout);

	ui->calcDisp->setText("0");

	disp_cleared = true;
	fractional = false;
}

void MainWindow::add_point() {
	if (fractional == false && ui->calcDisp->text().length() < MAXDIGITS - 1) {
		QString newDisp = ui->calcDisp->text() + ".";
		ui->calcDisp->setText(newDisp);
		fractional = true;
	}
}

MainWindow::~MainWindow() {
	delete ui;
}

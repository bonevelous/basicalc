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

#include "macros.h"
#include "enums.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

int is_frac = NOT_FRAC;

bool typing = false;

double last_ans = 0;
double cur_ans = 0;

function last_func = FUNC_NONE;

CalcButton *num_button[10];
CalcButton *pnt_button;
CalcButton *cls_button;
CalcButton *add_button;
CalcButton *sub_button;
CalcButton *mlt_button;
CalcButton *div_button;
CalcButton *ans_button;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow (parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	for (int i = 0; i < 10; i++) {
		QString curDigit = "digit_button" + QString::number(i);
		num_button[i] = MainWindow::findChild<CalcButton *>(curDigit);
		num_button[i]->set_num_val(i);
		connect(num_button[i], &CalcButton::released, this, &MainWindow::add_digit);
	}

	add_button = MainWindow::findChild<CalcButton *>("addButton");
	add_button->set_b_func(FUNC_ADD);
	connect(add_button, &CalcButton::released, this, &MainWindow::operation);

	/*sub_button = MainWindow::findChild<CalcButton *>("subtractButton");
	sub_button->set_b_func(FUNC_SUBTRACT);
	connect(sub_button, &CalcButton::released, this, &MainWindow::operation);*/

	ans_button = MainWindow::findChild<CalcButton *>("answerButton");
	ans_button->set_b_func(FUNC_ANSWER);
	connect(ans_button, &CalcButton::released, this, &MainWindow::operation);

	cls_button = MainWindow::findChild<CalcButton *>("clsButton");
	connect(cls_button, &QPushButton::released, this, &MainWindow::cls_display);

	pnt_button = MainWindow::findChild<CalcButton *>("pointButton");
	connect(pnt_button, &QPushButton::released, this, &MainWindow::add_point);
}

void MainWindow::clear_calc() {
	last_func = FUNC_NONE;
	last_ans = 0;
	cur_ans = 0;
	typing = false;
	is_frac = NOT_FRAC;
	last_func = FUNC_NONE;
}

void MainWindow::type_disp(int _num) {
	if (ui->calcDisp->text() == "0") {
		if (_num == 0 && is_frac == NOT_FRAC) ui->calcDisp->setText("0");
		else ui->calcDisp->setText(QString::number(_num));
	}
	else {
		QString newDisp = ui->calcDisp->text() + QString::number(_num);
		ui->calcDisp->setText(newDisp);
	}
}

void MainWindow::add_digit() {
	CalcButton *_btn = (CalcButton *)sender();
	QTextStream out(stdout);

	if (typing == false) {
		if (last_func == FUNC_NONE || last_func == FUNC_ANSWER) MainWindow::clear_calc();
		ui->calcDisp->setText(QString::number(_btn->num_val()));
		is_frac = NOT_FRAC;
		typing = true;
	}
	else {
		type_disp(_btn->num_val());
	}
}

void MainWindow::add_point() {
	if (is_frac == FRAC_UNCLEARED || typing == false) {
		if (last_func == FUNC_NONE || last_func == FUNC_ANSWER) MainWindow::clear_calc();
		ui->calcDisp->setText("0.");
		typing = true;
	}
	else if (is_frac == NOT_FRAC) {
		QString newDisp = ui->calcDisp->text() + ".";
		ui->calcDisp->setText(newDisp);
	}
	is_frac = IS_FRAC;
}

void MainWindow::set_disp() {
	QString new_ans = (is_frac == NOT_FRAC) ? QString::number((int) cur_ans) :
		QString::number(cur_ans);
	ui->calcDisp->setText(new_ans);
}

void MainWindow::operation() {
	CalcButton *_btn = (CalcButton *)sender();
	function m_func;
	is_frac = FRAC_UNCLEARED;

	if (_btn->b_func() != FUNC_ANSWER) {
		m_func = _btn->b_func();
		last_func = m_func;
	} else {
		m_func = last_func;
		last_func = _btn->b_func();;
	}

	if (typing == true) {
		switch (m_func) {
			case FUNC_ADD:
				last_ans = cur_ans;
				cur_ans = cur_ans + ui->calcDisp->text().toDouble();
				MainWindow::set_disp();
				break;
			default:
				break;
		}
		typing = false;
	}
}

void MainWindow::cls_display() {
	ui->calcDisp->setText("0");
	MainWindow::clear_calc();
}

MainWindow::~MainWindow() {
	delete ui;
}

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

#include "enums.h"
#include "macros.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "funcbutton.h"
#include "calcfunctions.h"

operEnum curOper = CALC_NONE;

//double storedMem = 0.0;
bool inputMode = false;
bool setNum = false;
double calcMem = 0.0;

QPushButton *calcDigit[10];
QPushButton *ansButton;

QPushButton *allClearButton;
QPushButton *swapButton;
QPushButton *delButton;

QPushButton *memStorBtn;
QPushButton *memRecBtn;
QPushButton *memClsBtn;
QPushButton *memAddBtn;
QPushButton *memSubBtn;

FuncButton *addButton;
FuncButton *subButton;
FuncButton *mulButton;
FuncButton *divButton;
FuncButton *modButton;

QAction *quitAct;

MainWindow::MainWindow(QWidget *parent) : 
	QMainWindow (parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	ui->calcEntry->setText(QString::number(calcMem));
	for (int i = 0; i < 10; i++) {
		QString curDigit = "button" + QString::number(i);
		calcDigit[i] = MainWindow::findChild<QPushButton *>(curDigit);
		connect(calcDigit[i], SIGNAL(released()), this, SLOT(digitRelease()));
	}

	allClearButton = MainWindow::findChild<QPushButton *>("buttonAllCls");
	connect(allClearButton, SIGNAL(released()), this, SLOT(allClear()));

	swapButton = MainWindow::findChild<QPushButton *>("buttonSign");
	connect(swapButton, SIGNAL(released()), this, SLOT(swapSign()));

	addButton = MainWindow::findChild<FuncButton *>("buttonAdd");
	addButton->setFunction(CALC_ADD);
	connect(addButton, SIGNAL(released()), this, SLOT(operPress()));

	subButton = MainWindow::findChild<FuncButton *>("buttonSubtract");
	subButton->setFunction(CALC_SUBTRACT);
	connect(subButton, SIGNAL(released()), this, SLOT(operPress()));

	mulButton = MainWindow::findChild<FuncButton *>("buttonMultiply");
	mulButton->setFunction(CALC_MULTIPLY);
	connect(mulButton, SIGNAL(released()), this, SLOT(operPress()));

	divButton = MainWindow::findChild<FuncButton *>("buttonDivide");
	divButton->setFunction(CALC_DIVIDE);
	connect(divButton, SIGNAL(released()), this, SLOT(operPress()));

	modButton = MainWindow::findChild<FuncButton *>("buttonModulus");
	modButton->setFunction(CALC_MODULUS);
	connect(modButton, SIGNAL(released()), this, SLOT(operPress()));

	ansButton = MainWindow::findChild<QPushButton *>("buttonAnswer");
	connect(ansButton, SIGNAL(released()), this, SLOT(answerPress()));

	delButton = MainWindow::findChild<QPushButton *>("buttonBack");
	connect(delButton, SIGNAL(released()), this, SLOT(deleteChar()));

	quitAct = MainWindow::findChild<QAction *>("actionQuit");
	connect(quitAct, &QAction::triggered, qApp, &QCoreApplication::quit, Qt::QueuedConnection);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::digitRelease() {
	QPushButton *button = (QPushButton *)sender();
	QString dspTxt = ui->calcEntry->text();

	if (inputMode == false) {
		if (curOper == CALC_NONE || curOper == CALC_ERROR) {
			calcMem = 0;
		}
		ui->calcEntry->setText(button->text());
		inputMode = true;
	} else {
		QString curVal = dspTxt + button->text();
		double tempMem = curVal.toDouble();
		ui->calcEntry->setText(QString::number(tempMem, 'g', MAX_DISPLAY_NUM));
	}
}

void calcAnswer(double gMem, double *gAns) {
	switch (curOper) {
		case CALC_ADD:
			*gAns = calcMem + gMem;
			calcMem = *gAns;
			break;
		case CALC_SUBTRACT:
			*gAns = calcMem - gMem;
			calcMem = *gAns;
			break;
		case CALC_MULTIPLY:
			*gAns = calcMem * gMem;
			calcMem = *gAns;
			break;
		case CALC_DIVIDE:
			if (gMem != 0) {
				*gAns = calcMem / gMem;
				calcMem = *gAns;
			} else {
				curOper = CALC_ERROR;
				calcMem = 0;
			}
			break;
		case CALC_MODULUS:
			*gAns = round(fmod(calcMem, gMem));
			calcMem = *gAns;
			break;
		default:
			break;
	}

	inputMode = false;
}

void MainWindow::operPress() {
	QTextStream out(stdout);

	FuncButton *button = (FuncButton *)sender();
	QString dspTxt = ui->calcEntry->text();
	operEnum gFunc = button->function();
	calcMem = dspTxt.toDouble();

	inputMode = false;

	switch (gFunc) {
		case CALC_ADD:
			curOper = CALC_ADD;
			break;
		case CALC_SUBTRACT:
			curOper = CALC_SUBTRACT;
			break;
		case CALC_MULTIPLY:
			curOper = CALC_MULTIPLY;
			break;
		case CALC_DIVIDE:
			curOper = CALC_DIVIDE;
			break;
		case CALC_MODULUS:
			curOper = CALC_MODULUS;
			break;
		default:
			break;
	}

	if (setNum == true) {
		QString dspTxt = ui->calcEntry->text();
		double dspMem = dspTxt.toDouble();
		double calcAns = 0;
		calcAnswer(dspMem, &calcAns);

		if (curOper != CALC_ERROR) {
			ui->calcEntry->setText(QString::number(calcAns, 'g', MAX_DISPLAY_NUM));
		} else {
			ui->calcEntry->setText("ERROR");
		}
	} else {
		setNum = true;
	}
}

void MainWindow::allClear() {
	setNum = false;
	inputMode = false;
	curOper = CALC_NONE;
	ui->calcEntry->setText("0");
}

void MainWindow::swapSign() {
	QString dspTxt = ui->calcEntry->text();
	double dspMem = dspTxt.toDouble() * -1;
	ui->calcEntry->setText(QString::number(dspMem, 'g', MAX_DISPLAY_NUM));
}

void MainWindow::answerPress() {
	inputMode = false;
	setNum = false;
	QString dspTxt = ui->calcEntry->text();
	double dspMem = dspTxt.toDouble();
	double calcAns = 0;

	calcAnswer(dspMem, &calcAns);

	if (curOper != CALC_ERROR) {
		ui->calcEntry->setText(QString::number(calcAns, 'g', MAX_DISPLAY_NUM));
	} else {
		ui->calcEntry->setText("ERROR");
	}

	curOper = CALC_NONE;
}

void MainWindow::deleteChar() {
	QString dspTxt = ui->calcEntry->text();
	if (dspTxt.length() > 1) {
		dspTxt.chop(1);
	} else {
		dspTxt = "0";
	}

	ui->calcEntry->setText(dspTxt);
}

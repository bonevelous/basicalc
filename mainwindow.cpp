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

#include "calcfunctions.h"

#include "funcbutton.h"
#include "membutton.h"

operEnum curOper = OPERATION_NONE;

bool inputMode = false;
bool setNum = false;

double calcMem = 0.0;
double lastAns = 0.0;

QPushButton *calcDigit[10];
QPushButton *ansButton;

QPushButton *allClearButton;
QPushButton *delButton;
QPushButton *dotButton;

MemButton *memSavBtn;
MemButton *memClsBtn;
MemButton *memRecBtn;
MemButton *memAddBtn;
MemButton *memSubBtn;

FuncButton *swapButton;
FuncButton *addButton;
FuncButton *subButton;
FuncButton *mulButton;
FuncButton *divButton;
//FuncButton *powButton;
//FuncButton *sqrtButton;
FuncButton *modButton;

QAction *quitAct;

MainWindow::MainWindow(QWidget *parent) : 
	QMainWindow (parent), ui(new Ui::MainWindow) {

	ui->setupUi(this);

	ui->calcEntry->setText(QString::number(lastAns));
	for (int i = 0; i < 10; i++) {
		QString curDigit = "button" + QString::number(i);
		calcDigit[i] = MainWindow::findChild<QPushButton *>(curDigit);
		connect(calcDigit[i], SIGNAL(released()), this, SLOT(digitRelease()));
	}

	allClearButton = MainWindow::findChild<QPushButton *>("buttonAllCls");
	connect(allClearButton, &QPushButton::released, this, &MainWindow::allClear);

	swapButton = MainWindow::findChild<FuncButton *>("buttonSign");
	swapButton->setFunction(OPERATION_SIGN_SWAP);
	connect(swapButton, &FuncButton::released, this, &MainWindow::operPress);

	addButton = MainWindow::findChild<FuncButton *>("buttonAdd");
	addButton->setFunction(OPERATION_ADD);
	connect(addButton, &FuncButton::released, this, &MainWindow::operPress);

	subButton = MainWindow::findChild<FuncButton *>("buttonSubtract");
	subButton->setFunction(OPERATION_SUBTRACT);
	connect(subButton, &FuncButton::released, this, &MainWindow::operPress);

	mulButton = MainWindow::findChild<FuncButton *>("buttonMultiply");
	mulButton->setFunction(OPERATION_MULTIPLY);
	connect(mulButton, &FuncButton::released, this, &MainWindow::operPress);

	divButton = MainWindow::findChild<FuncButton *>("buttonDivide");
	divButton->setFunction(OPERATION_DIVIDE);
	connect(divButton, &FuncButton::released, this, &MainWindow::operPress);

	modButton = MainWindow::findChild<FuncButton *>("buttonModulus");
	modButton->setFunction(OPERATION_MODULUS);
	connect(modButton, &FuncButton::released, this, &MainWindow::operPress);

	ansButton = MainWindow::findChild<QPushButton *>("buttonAnswer");
	connect(ansButton, &QPushButton::released, this, &MainWindow::answerPress);

	dotButton = MainWindow::findChild<QPushButton *>("buttonDot");
	connect(dotButton, &QPushButton::released, this, &MainWindow::addPoint);

	delButton = MainWindow::findChild<QPushButton *>("buttonBack");
	connect(delButton, &QPushButton::released, this, &MainWindow::deleteChar);

	/*memSavBtn = MainWindow::findChild<MemButton *>("buttonMS");
	memSavBtn->setMemFunc(MEMORY_STORE);
	connect(memSavBtn, &MemButton::released, this, &MainWindow::memoryPress);

	memClsBtn = MainWindow::findChild<MemButton *>("buttonMC");
	memClsBtn->setMemFunc(MEMORY_CLEAR);
	connect(memClsBtn, &MemButton::released, this, &MainWindow::memoryPress);

	memRecBtn = MainWindow::findChild<MemButton *>("buttonMR");
	memRecBtn->setMemFunc(MEMORY_RECALL);
	connect(memRecBtn, &MemButton::released, this, &MainWindow::memoryPress);

	memAddBtn = MainWindow::findChild<MemButton *>("buttonMAdd");
	memAddBtn->setMemFunc(MEMORY_ADD);
	connect(memAddBtn, &MemButton::released, this, &MainWindow::memoryPress);

	memSubBtn = MainWindow::findChild<MemButton *>("buttonMSub");
	memSubBtn->setMemFunc(MEMORY_SUBTRACT);
	connect(memSubBtn, &MemButton::released, this, &MainWindow::memoryPress);*/

	quitAct = MainWindow::findChild<QAction *>("actionQuit");
	connect(quitAct, &QAction::triggered, qApp, &QCoreApplication::quit, Qt::QueuedConnection);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::digitRelease() {
	QPushButton *button = (QPushButton *)sender();
	QString dspText = ui->calcEntry->text();

	if (inputMode == false) {
		if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) {
			lastAns = 0;
		}
		ui->calcEntry->setText(button->text());
		if (ui->calcEntry->text() != "0") {
			inputMode = true;
		}
	} else {
		if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
			QString curVal = dspText + button->text();
			ui->calcEntry->setText(curVal);
		} else {
			qDebug() << "Max display numbers reached";
		}
	}
}

void MainWindow::addPoint() {
	QPushButton *button = (QPushButton *)sender();
	QString dspText = ui->calcEntry->text();

	if (inputMode == false) {
		inputMode = true;
		ui->calcEntry->setText("0.");
	} else {
		if (!ui->calcEntry->text().contains('.')) {
			QString curVal = dspText + button->text();
			ui->calcEntry->setText(curVal);
		} else {
			qDebug() << "Cannot set fractional, already fractional";
		}
	}
}

void calcAnswer(double gMem, double *gAns) {
	switch (curOper) {
		case OPERATION_ADD:
			*gAns = lastAns + gMem;
			lastAns = *gAns;
			break;
		case OPERATION_SUBTRACT:
			*gAns = lastAns - gMem;
			lastAns = *gAns;
			break;
		case OPERATION_MULTIPLY:
			*gAns = lastAns * gMem;
			lastAns = *gAns;
			break;
		case OPERATION_DIVIDE:
			if (gMem != 0) {
				*gAns = lastAns / gMem;
				lastAns = *gAns;
			} else {
				curOper = OPERATION_ERROR;
				lastAns = 0;
			}
			break;
		case OPERATION_MODULUS:
			*gAns = round(fmod(lastAns, gMem));
			lastAns = *gAns;
			break;
		case OPERATION_SIGN_SWAP:
			*gAns = -gMem;
			lastAns = *gAns;
			break;
		default:
			break;
	}

	inputMode = false;
}

void MainWindow::operPress() {
	QTextStream out(stdout);

	FuncButton *button = (FuncButton *)sender();
	QString dspText = ui->calcEntry->text();
	curOper = button->function();
	lastAns = dspText.toDouble();

	if (curOper == OPERATION_SIGN_SWAP) setNum = true;

	inputMode = false;

	if (setNum == true) {
		QString dspText = ui->calcEntry->text();
		double dspMem = dspText.toDouble();
		double calcAns = 0;
		calcAnswer(dspMem, &calcAns);

		if (curOper != OPERATION_ERROR) {
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
	curOper = OPERATION_NONE;
	ui->calcEntry->setText("0");
}

void MainWindow::answerPress() {
	if (setNum == true) {
		setNum = false;
		inputMode = false;

		QString dspText = ui->calcEntry->text();
		double dspMem = dspText.toDouble();
		double calcAns = 0;

		calcAnswer(dspMem, &calcAns);

		if (curOper != OPERATION_ERROR) {
			ui->calcEntry->setText(QString::number(calcAns, 'g', MAX_DISPLAY_NUM));
		} else {
			ui->calcEntry->setText("ERROR");
		}

		curOper = OPERATION_NONE;
	}
}

void MainWindow::deleteChar() {
	QString dspText = ui->calcEntry->text();
	if (dspText.length() > 1) {
		dspText.chop(1);
	} else {
		dspText = "0";
	}

	ui->calcEntry->setText(dspText);
}

void MainWindow::memoryPress() {
	MemButton *button = (MemButton *)sender();
	memBtnEnum gMem = button->memFunc();
	QString dspText = ui->calcEntry->text();
	double dspMem = dspText.toDouble();

	switch (gMem) {
		case MEMORY_STORE:
			calcMem = dspMem;
			memRecBtn->setEnabled(true);
			break;
		case MEMORY_CLEAR:
			calcMem = 0.0;
			memRecBtn->setEnabled(false);
			break;
		case MEMORY_RECALL:
			dspMem = calcMem;
			ui->calcEntry->setText(QString::number(dspMem, 'g', MAX_DISPLAY_NUM));
			break;
		case MEMORY_ADD:
			if (memRecBtn->isEnabled() == false) {
				calcMem = dspMem;
				memRecBtn->setEnabled(true);
			} else {
				calcMem += dspMem;
			}
			break;
		case MEMORY_SUBTRACT:
			if (memRecBtn->isEnabled() == false) {
				calcMem = -dspMem;
				memRecBtn->setEnabled(true);
			} else {
				calcMem -= dspMem;
			}
			break;
		default:
			break;
	}
}

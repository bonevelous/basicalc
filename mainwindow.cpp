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
#include "constbutton.h"

operEnum curOper = OPERATION_NONE;

bool inputMode = false;
bool setNum = false;
bool altMode = false;

double calcMem = 0.0;
double lastAns = 0.0;

QPushButton *calcDigit[10];
QPushButton *ansButton;
QPushButton *allClearButton;
QPushButton *delButton;
QPushButton *dotButton;
QPushButton *altButton;

MemButton *memSavBtn;
MemButton *memClsBtn;
MemButton *memRecBtn;
MemButton *memAltBtn;

FuncButton *addButton;
FuncButton *subButton;
FuncButton *mulButton;
FuncButton *divButton;
FuncButton *powButton;
FuncButton *rootButton;

FuncButton *swapButton;
FuncButton *factButton;
FuncButton *modButton;
FuncButton *absButton;

FuncButton *sinButton;
FuncButton *cosButton;
FuncButton *tanButton;
FuncButton *cscButton;
FuncButton *secButton;
FuncButton *cotButton;

FuncButton *logButton;
FuncButton *lnButton;

ConstButton *clearEntryButton;
ConstButton *piButton;
ConstButton *eulerButton;

QAction *quitAct;
QKeyEvent *keyEvent;

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

	powButton = MainWindow::findChild<FuncButton *>("buttonPower");
	powButton->setFunction(OPERATION_POWER);
	connect(powButton, &FuncButton::released, this, &MainWindow::operPress);

	rootButton = MainWindow::findChild<FuncButton *>("buttonRoot");
	rootButton->setFunction(OPERATION_ROOT);
	connect(rootButton, &FuncButton::released, this, &MainWindow::operPress);

	modButton = MainWindow::findChild<FuncButton *>("buttonModulus");
	modButton->setFunction(OPERATION_MODULUS);
	connect(modButton, &FuncButton::released, this, &MainWindow::operPress);

	ansButton = MainWindow::findChild<QPushButton *>("buttonAnswer");
	connect(ansButton, &QPushButton::released, this, &MainWindow::answerPress);

	dotButton = MainWindow::findChild<QPushButton *>("buttonDot");
	connect(dotButton, &QPushButton::released, this, &MainWindow::addPoint);

	delButton = MainWindow::findChild<QPushButton *>("buttonBack");
	connect(delButton, &QPushButton::released, this, &MainWindow::deleteChar);

	memSavBtn = MainWindow::findChild<MemButton *>("buttonMS");
	memSavBtn->setMemFunc(MEMORY_STORE);
	connect(memSavBtn, &MemButton::released, this, &MainWindow::memoryPress);

	memClsBtn = MainWindow::findChild<MemButton *>("buttonMC");
	memClsBtn->setMemFunc(MEMORY_CLEAR);
	connect(memClsBtn, &MemButton::released, this, &MainWindow::memoryPress);

	memRecBtn = MainWindow::findChild<MemButton *>("buttonMR");
	memRecBtn->setMemFunc(MEMORY_RECALL);
	connect(memRecBtn, &MemButton::released, this, &MainWindow::memoryPress);

	memAltBtn = MainWindow::findChild<MemButton *>("buttonMAlt");
	memAltBtn->setMemFunc(MEMORY_ALT);
	connect(memAltBtn, &MemButton::released, this, &MainWindow::memoryPress);

	altButton = MainWindow::findChild<QPushButton *>("buttonAltMode");
	connect(altButton, &QPushButton::released, this, &MainWindow::altPress);

	clearEntryButton = MainWindow::findChild<ConstButton *>("buttonClsEntry");
	connect(clearEntryButton, &ConstButton::released, this, &MainWindow::setDspToConst);

	piButton = MainWindow::findChild<ConstButton *>("buttonPi");
	piButton->setConst(M_PI);
	connect(piButton, &ConstButton::released, this, &MainWindow::setDspToConst);

	eulerButton = MainWindow::findChild<ConstButton *>("buttonEuler");
	eulerButton->setConst(exp(1));
	connect(eulerButton, &ConstButton::released, this, &MainWindow::setDspToConst);

	factButton = MainWindow::findChild<FuncButton *>("buttonFactorial");
	factButton->setFunction(OPERATION_FACTORIAL);
	connect(factButton, &FuncButton::released, this, &MainWindow::operPress);

	absButton = MainWindow::findChild<FuncButton *>("buttonAbsolute");
	absButton->setFunction(OPERATION_ABSOLUTE);
	connect(absButton, &FuncButton::released, this, &MainWindow::operPress);

	sinButton = MainWindow::findChild<FuncButton *>("buttonSIN");
	sinButton->setFunction(OPERATION_SIN);
	connect(sinButton, &FuncButton::released, this, &MainWindow::operPress);

	cosButton = MainWindow::findChild<FuncButton *>("buttonCOS");
	cosButton->setFunction(OPERATION_COS);
	connect(cosButton, &FuncButton::released, this, &MainWindow::operPress);

	tanButton = MainWindow::findChild<FuncButton *>("buttonTAN");
	tanButton->setFunction(OPERATION_TAN);
	connect(tanButton, &FuncButton::released, this, &MainWindow::operPress);

	cscButton = MainWindow::findChild<FuncButton *>("buttonCSC");
	cscButton->setFunction(OPERATION_CSC);
	connect(cscButton, &FuncButton::released, this, &MainWindow::operPress);

	secButton = MainWindow::findChild<FuncButton *>("buttonSEC");
	secButton->setFunction(OPERATION_SEC);
	connect(secButton, &FuncButton::released, this, &MainWindow::operPress);

	cotButton = MainWindow::findChild<FuncButton *>("buttonCOT");
	cotButton->setFunction(OPERATION_COT);
	connect(cotButton, &FuncButton::released, this, &MainWindow::operPress);

	logButton = MainWindow::findChild<FuncButton *>("buttonLog");
	logButton->setFunction(OPERATION_LOG);
	connect(logButton, &FuncButton::released, this, &MainWindow::operPress);

	lnButton = MainWindow::findChild<FuncButton *>("buttonLN");
	lnButton->setFunction(OPERATION_LN);
	connect(lnButton, &FuncButton::released, this, &MainWindow::operPress);

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
		if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
		ui->calcEntry->setText(button->text());
		if (ui->calcEntry->text() != "0") inputMode = true;
	} else {
		if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
			QString curVal = dspText + button->text();
			ui->calcEntry->setText(curVal);
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
		}
	}
}

void MainWindow::operPress() {
	QTextStream out(stdout);

	FuncButton *button = (FuncButton *)sender();
	QString dspText = ui->calcEntry->text();
	curOper = button->function();

	if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = dspText.toDouble();
	if (curOper != OPERATION_SIGN_SWAP) inputMode = false;

	if (setNum == true || calcInstaAns(curOper) == true) {
		inputMode = false;

		QString dspText = ui->calcEntry->text();
		double dspMem = dspText.toDouble();
		calcAnswer(&curOper, dspMem, &lastAns, altMode);

		curOper == OPERATION_ERROR ? ui->calcEntry->setText("ERROR") : \
			ui->calcEntry->setText(QString::number(lastAns, 'g', MAX_DISPLAY_NUM));
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
		calcAnswer(&curOper, dspMem, &lastAns, altMode);

		curOper == OPERATION_ERROR ? ui->calcEntry->setText("ERROR") : \
			ui->calcEntry->setText(QString::number(lastAns, 'g', MAX_DISPLAY_NUM));

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
			inputMode = false;
			break;
		case MEMORY_ALT:
			if (memRecBtn->isEnabled() == false) {
				altMode == true ? calcMem = -dspMem : calcMem = dspMem;
				memRecBtn->setEnabled(true);
			} else {
				altMode == true ? calcMem -= dspMem : calcMem += dspMem;
			}
			break;
		default:
			break;
	}
}

void MainWindow::altPress() {
	altMode = !altMode;
	if (altMode == true) {
		memAltBtn->setText("M-");
		sinButton->setText("ASIN");
		sinButton->setText("ACOS");
		sinButton->setText("ATAN");
		sinButton->setText("ACSC");
		sinButton->setText("ASEC");
		sinButton->setText("ACOT");
	} else {
		memAltBtn->setText("M+");
		sinButton->setText("SIN");
		sinButton->setText("COS");
		sinButton->setText("TAN");
		sinButton->setText("CSC");
		sinButton->setText("SEC");
		sinButton->setText("COT");
	}
}

void MainWindow::setDspToConst() {
	ConstButton *button = (ConstButton *)sender();
	ui->calcEntry->setText(QString::number(button->storedConst(), 'g', MAX_DISPLAY_NUM));
	lastAns = button->storedConst();
	inputMode = false;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	switch (event->key()) {
		case Qt::Key_0:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("0");
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "1";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_1:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("1");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "1";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_2:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("2");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "2";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_3:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("3");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "3";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_4:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("4");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "4";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_5:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("5");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "5";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_6:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("6");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "6";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_7:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("7");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "7";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_8:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("8");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "8";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		case Qt::Key_9:
			{
				QString dspText = ui->calcEntry->text();

				if (inputMode == false) {
					if (curOper == OPERATION_NONE || curOper == OPERATION_ERROR) lastAns = 0;
					ui->calcEntry->setText("9");
					inputMode = true;
				} else {
					if (ui->calcEntry->text().length() < MAX_DISPLAY_NUM) {
						QString curVal = dspText + "9";
						ui->calcEntry->setText(curVal);
					}
				}
				break;
			}
		default:
			break;
	}
}

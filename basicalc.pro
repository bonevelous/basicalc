################################################################################
#
#    Basicalc - Basic QT Calculator
#    Copyright (C) 2023	Matthew Gobbi
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
################################################################################

VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 1

TEMPLATE += app
CONFIG += c++20

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
	"VERSION_MINOR=$$VERSION_MINOR"\
	"VERSION_BUILD=$$VERSION_BUILD"

VERSION += $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

SOURCES += \
	main.cpp \
	mainwindow.cpp \
	funcbutton.cpp \
	membutton.cpp \
	constbutton.cpp \
	calcfunctions.cpp

HEADERS += \
	mainwindow.h \
	funcbutton.h \
	membutton.h \
	constbutton.h \
	calcfunctions.h


FORMS += \
	mainwindow.ui

QT += widgets core gui

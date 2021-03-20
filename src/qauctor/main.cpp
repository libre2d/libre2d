/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * main.cpp - qauctor - The libre2d control application
 */

#include <QApplication>

#include "main_window.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	int ret;

	MainWindow *mainWindow = new MainWindow();
	mainWindow->show();
	ret = app.exec();
	delete mainWindow;

	return ret;
}

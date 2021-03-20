/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * main_window.cpp - qauctor - Main application window
 */

#include "main_window.h"

MainWindow::MainWindow()
{
	createToolbars();

	// \todo append model name
	title_ = "libre2d qauctor";
	setWindowTitle(title_);

	// \todo connect slot to canvas render
}

MainWindow::~MainWindow()
{
}

int MainWindow::createToolbars()
{
	toolbar_ = addToolBar("qauctor toolbar");

	toolbar_->setContextMenuPolicy(Qt::PreventContextMenu);

	return 0;
}

void MainWindow::quit()
{
}

void MainWindow::updateTitle()
{
}

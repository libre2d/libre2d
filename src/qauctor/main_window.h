/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * main_window.h - qauctor - Main application window
 */
#ifndef __QAUCTOR_MAIN_WINDOW_H__
#define __QAUCTOR_MAIN_WINDOW_H__

#include <QMainWindow>
#include <QToolBar>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

private Q_SLOTS:
	void quit();
	void updateTitle();

private:
	int createToolbars();

	/* UI elements */
	QToolBar *toolbar_;
	//Canvas *canvas_;

	QString title_;
};

#endif /* __QAUCTOR_MAIN_WINDOW_H__ */

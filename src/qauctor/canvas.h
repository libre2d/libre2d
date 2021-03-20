/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * canvas.h - qauctor - Canvas class
 */
#ifndef __QAUCTOR_CANVAS_H__
#define __QAUCTOR_CANVAS_H__

#include <QImage>
#include <QMutex>
#include <QWidget>

#include <libre2d/buffer.h>

class Canvas : public QWidget
{
	Q_OBJECT
public:
	Canvas();
	~Canvas();

	void render(libre2d::FrameBuffer *buffer);

private:
	QImage image_;
	QMutex mutex_;
};

#endif /* __QAUCTOR_CANVAS_H__ */

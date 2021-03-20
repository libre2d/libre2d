/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * canvas.cpp - qauctor - Canvas class
 */

#include "canvas.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{
}

void Canvas::render(libre2d::FrameBuffer *buffer)
{
	{
		QMutexLocker locker(&mutex_);
		image_ = QImage(buffer->data, buffer->width, buffer->height,
				buffer->stride, QImage::Format_ARGB32);
	}

	update();
}

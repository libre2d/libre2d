/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * buffer.h - Buffer
 */

#ifndef __LIBRE2D_BUFFER_H__
#define __LIBRE2D_BUFFER_H__

namespace libre2d {

struct FrameBuffer
{
	unsigned char *data;
	size_t width;
	size_t height;
	size_t stride;
};

} /* namespace libre2d */

#endif /* __LIBRE2D_BUFFER_H__ */

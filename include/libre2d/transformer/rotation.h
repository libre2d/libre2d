/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * rotation.h - A mesh rotation transformer
 */

#ifndef __LIBRE2D_TRANSFORMER_ROTATION_H__
#define __LIBRE2D_TRANSFORMER_ROTATION_H__

#include <map>

#include <libre2d/geometry.h>
#include <libre2d/transformer.h>

namespace libre2d {

class TransformerRotation : public Transformer
{
public:
	~TransformerRotation() { }

	Mesh transform(const Mesh &mesh, float param,
		       enum TransformWhom whom);

	float offset;
	Vertex center;
};

} /* namespace libre2d */

#endif /* __LIBRE2D_TRANSFORMER_ROTATION_H__ */

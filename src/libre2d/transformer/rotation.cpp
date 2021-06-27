/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * rotation.cpp - A mesh substitution transformer
 */

#include <libre2d/transformer/rotation.h>

#include <algorithm>
#include <cmath>

namespace libre2d {

/*
 * \todo validate offset between -360 and +360
 */

/**
 * \var TransformerRotation::offset
 * \brief The number of clockwise degrees from global "up" that will be
 * considered "up" for the Component.
 */

/**
 * \brief Set the parameter value and output the resulting Mesh
 * \param[in] mesh The mesh to rotate
 * \param[in] param The number of clockwise degrees plus the offset to set the Mesh to.
 * \return The result Mesh from setting the parameter value.
 *
 * \todo confirm that copy elision works
 */
Mesh TransformerRotation::transform(const Mesh &mesh, float param,
				    enum TransformWhom whom)
{
	float modParam = std::fmod(param, 360);
	float modAngle = std::fmod(modParam + offset, 360);
	float revAngle = std::fmod(360 - modAngle, 360);

	if (whom == Self)
		center = mesh.centerVertex();

	return mesh.rotate(revAngle, center);
}

} /* namespace libre2d */

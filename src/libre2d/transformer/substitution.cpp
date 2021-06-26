/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * substitution.cpp - A mesh substitution transformer
 */

#include <libre2d/transformer/substitution.h>

namespace libre2d {

/*
 * \todo polymorph validation
 * min, max, default need key meshes
 * \todo documentation
 */

/**
 * \brief Set the parameter value and output the resulting Mesh
 * \param[in] param The parameter value to set
 * \return The result Mesh from setting the parameter value. If the
 * value is out of range, it will be clamped.
 *
 * \todo confirm that copy elision works
 */
Mesh TransformerSubstitution::transform([[maybe_unused]] const Mesh &mesh,
					float param) const
{
	if (param <= info->min)
		return keyMeshes.at(info->min);

	if (param >= info->max)
		return keyMeshes.at(info->max);

	const auto &lower = keyMeshes.lower_bound(param);
	const auto &upper = keyMeshes.upper_bound(param);

	/* We have exact match */
	if (lower != upper)
		return lower->second;

	const auto &realLower = std::prev(lower);
	float lowerDist = param - realLower->first;

	/* Round for discrete (because we're using floats) */
	if (info->type == Discrete) {
		float upperDist = upper->first - param;
		if (upperDist > lowerDist)
			return realLower->second;
		return upper->second;
	}

	/* Interpolate for continuous */
	float factor = lowerDist / (upper->first - realLower->first);
	Mesh ret = realLower->second;
	ret.interpolateInPlace(upper->second, factor);
	return ret;
}

} /* namespace libre2d */

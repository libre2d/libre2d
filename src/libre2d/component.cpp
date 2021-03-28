/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * component.cpp - A container for a Component of a Model
 */

#include <libre2d/component.h>

#include <iostream>
#include <map>

/**
 * \file component.h
 * \brief Data structures related to a Component of a Model
 */

namespace libre2d {

/**
 * \class Parameter
 * \brief Describes a Parameter for a Component, and the KeyFrames
 *
 * A Parameter contains the key values and the key frames for the
 * transformation of containing Component. It also handles interpolation of
 * parameter values between key values, and can output interpolated KeyFrames.
 *
 * \todo document the enum
 * \todo cache previous setParameter() results
 * \todo finish the documentation
 * \todo set up logging
 */

/**
 * \var Parameter::name
 * \brief The name of the parameter
 *
 * This is used to link with other parameters in the Model
 *
 * \todo figure out how to link rotation and scaling. add keyRotations and
 * keyScaling vectors? not sure how order of operations will work.
 */

/**
 * \var Parameter::type
 * \brief The type of the parameter, either disrete or continuous
 */

/**
 * \var Parameter::min
 * \brief The minimum value of the parameter
 */

/**
 * \var Parameter::max
 * \brief The maximum value of the parameter
 */

/**
 * \var Parameter::keyMeshes
 * \brief The key values and key frames of the parameter
 */

bool Parameter::validate() const
{
	bool valid = true;

	if (info->min > info->max) {
		std::cerr << "ERROR Parameter: min is greater than max" << std::endl;
		valid = false;
	}
	
	if (keyMeshes.find(info->min) == keyMeshes.end()) {
		std::cerr << "ERROR Parameter: no keyframe for min" << std::endl;
		valid = false;
	}

	if (keyMeshes.find(info->max) == keyMeshes.end()) {
		std::cerr << "ERROR Parameter: no keyframe for max" << std::endl;
		valid = false;
	}

	if (keyMeshes.find(info->defaultValue) == keyMeshes.end()) {
		std::cerr << "ERROR Parameter: no keyframe for default" << std::endl;
		valid = false;
	}

	/* \todo check the number of vertices in all meshes and all anchor lists */

	return valid;
}

/**
 * \brief Set the parameter value and output the resulting Mesh
 * \param[in] param The parameter value to set
 * \return The result Mesh from setting the parameter value. If the
 * value is out of range, it will be clamped.
 *
 * \todo confirm that copy elision works
 */
Mesh Parameter::setParameter(float param) const
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

/**
 * \class Component
 * \brief Describes a Component of a Model
 *
 * A Component is a grouping of a mesh, uv-mapping, parameters, and children
 * Components. In the example of a Model of a humanoid face, a Component might
 * describe a blank face, and there would be different children Components to
 * describe each eye, nose, mouth, etc.
 *
 * The mesh of the Component describes the current Mesh that the Component
 * is taking. The Parameters contain the necessary information for transforming
 * the current mesh. The position of children Components are mapped using the
 * anchor points of the parent Component, and the transformation center point
 * of the child Component.
 *
 * \todo finish the documentation
 * \todo implement validate
 */

bool Component::validate() const
{
	/*
	 * \todo validate the length of the children list with the anchor list
	 * length of the KeyFrames in the Parameters
	 * length of vertices in the meshes (recurse into parameter validation?)
	 */
	return true;
}

/**
 * \brief Reset the current mesh of the Component to default parameter values
 *
 * This preserves the center point position (as a parent might have translated
 * it via anchor points).
 */
void Component::reset()
{
	bool first = true;

	Vertex origin = currentMesh.centerVertex();

	for (auto pair : parameters) {
		float value = pair.second.info->defaultValue;
		if (first) {
			currentMesh = pair.second.keyMeshes.at(value);
			first = false;
			continue;
		}

		currentMesh.interpolateInPlace(pair.second.keyMeshes.at(value), 0.5);
	}

	currentMesh.translateToPointInPlace(origin);

	moveChildren();
}

/**
 * \brief Set the parameters on the current Component
 * \param[in] params Map of parameter name to parameter value
 *
 * This also moves the children after the anchors are moved
 */
void Component::setParameters(const std::map<std::string, float> &params)
{
	/* \todo optimize the reset (skip the parameters that we'll overwrite) */
	reset();

	for (auto pair : params) {
		const std::string &paramName = pair.first;
		float value = pair.second;

		/* skip the parameter if it doesn't apply to us */
		auto parameter = parameters.find(paramName);
		if (parameter == parameters.end())
			continue;

		currentMesh.interpolateInPlace(parameter->second.setParameter(value), 0.5);
	}

	moveChildren();
}

/**
 * \brief Move the children Components to match the anchors
 *
 * This should be called after any transformation is made to the currentMesh
 */
void Component::moveChildren()
{
	for (Component &child : children) {
		const Vertex &anchor = currentMesh.anchorVertex(child.name);
		child.currentMesh.translateToPointInPlace(anchor);
	}
}

} /* namespace libre2d */

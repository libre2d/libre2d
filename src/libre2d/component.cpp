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
 * \class KeyFrame
 * \brief Describes a Mesh in an endpoint of a Parameter for a Component
 *
 * A KeyFrame is a grouping of a Mesh, a center of transformation, and a list
 * of anchor vertices. The KeyFrame describes a key point in a Parameter of a
 * Component, and designates the Mesh that the Component should be for the
 * given value of the Parameter.
 */

/**
 * \var KeyFrame::mesh
 * \brief The Mesh that the KeyFrame represents
 */

/**
 * \var KeyFrame::center
 * \brief The center Vertex of all transformation operations on the Mesh
 */

/**
 * \var KeyFrame::anchors
 * \brief The anchor points for all children Meshes (for the Component)
 */

void KeyFrame::interpolateInPlace(const KeyFrame &other, float factor)
{
	mesh.interpolateInPlace(other.mesh, factor);
	center.interpolateInPlace(other.center, factor);

	for (auto &pair : anchors)
		pair.second.interpolateInPlace(other.anchors.at(pair.first), factor);
}

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
 * \var Parameter::keyFrames
 * \brief The key values and key frames of the parameter
 */

bool Parameter::validate() const
{
	bool valid = true;

	if (info->min > info->max) {
		std::cerr << "ERROR Parameter: min is greater than max" << std::endl;
		valid = false;
	}
	
	if (keyFrames.find(info->min) == keyFrames.end()) {
		std::cerr << "ERROR Parameter: no keyframe for min" << std::endl;
		valid = false;
	}

	if (keyFrames.find(info->max) == keyFrames.end()) {
		std::cerr << "ERROR Parameter: no keyframe for max" << std::endl;
		valid = false;
	}

	/* \todo check the number of vertices in all meshes and all anchor lists */

	return valid;
}

/**
 * \brief Set the parameter value and output the resulting KeyFrame
 * \param[in] param The parameter value to set
 * \return The result KeyFrame from setting the parameter value. If the
 * value is out of range, it will be clamped.
 *
 * \todo confirm that copy elision works
 */
KeyFrame Parameter::setParameter(float param) const
{
	if (param <= info->min)
		return keyFrames.at(info->min);

	if (param >= info->max)
		return keyFrames.at(info->max);

	const auto &lower = keyFrames.lower_bound(param);
	const auto &upper  = keyFrames.upper_bound(param);

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
	KeyFrame ret = realLower->second;
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
	 */
	return true;
}

void Component::setParameter(const std::string &paramName, float value)
{
	/* \todo optimize: skip this if it's called from the vector setParameter() */
	auto parameter = parameters.find(paramName);
	if (parameter == parameters.end()) {
		std::cerr << "ERROR Component: invalid parameter " << paramName << std::endl;
		return;
	}

	/* \todo handle resetting the currentFrame */
	currentFrame.interpolateInPlace(parameter->second.setParameter(value), 0.5);

	/* \todo optimize: skip this if it's called from the vector setParameter() */
	for (Component &child : children) {
		const Vertex &anchor = currentFrame.anchors.at(child.name);
		const KeyFrame &childFrame = child.currentFrame;
		Vector transVec(anchor.x - childFrame.center.x,
				anchor.y - childFrame.center.y);
		child.currentFrame.translateInPlace(transVec);
	}
}

void Component::setParameter(const std::map<std::string, float> &params)
{
	for (auto pair : params)
		setParameter(pair.first, pair.second);
}

} /* namespace libre2d */

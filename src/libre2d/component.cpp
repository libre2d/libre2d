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

	/* \todo check the number of vertices in all meshes and all anchor lists */

	return valid;
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

void Component::setParameter(const std::string &paramName, [[maybe_unused]] float value)
{
	/* \todo implement this whole thing */

	/* \todo optimize: skip this if it's called from the vector setParameter() */
	auto parameter = parameters.find(paramName);
	if (parameter == parameters.end()) {
		std::cerr << "ERROR Component: invalid parameter " << paramName << std::endl;
		return;
	}

	/* \todo handle resetting the currentFrame */
	//currentMesh.interpolateInPlace(parameter->second.setParameter(value), 0.5);

	/* \todo optimize: skip this if it's called from the vector setParameter() */
	/* \todo use convenience methods for these */
	for (Component &child : children) {
		const Vertex &anchor = currentMesh.vertices.at(currentMesh.anchors.at(child.name));
		const Mesh &childMesh = child.currentMesh;
		const Vertex &childCenter = childMesh.vertices.at(childMesh.center);
		Vector transVec(anchor.x - childCenter.x,
				anchor.y - childCenter.y);
		child.currentMesh.translateInPlace(transVec);
	}
}

void Component::setParameter(const std::map<std::string, float> &params)
{
	for (auto pair : params)
		setParameter(pair.first, pair.second);
}

} /* namespace libre2d */

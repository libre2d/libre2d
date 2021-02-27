/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * component.h - A container for a Component of a Model
 */

#ifndef __LIBRE2D_COMPONENT_H__
#define __LIBRE2D_COMPONENT_H__

#include <map>
#include <string>
#include <vector>

#include <libre2d/geometry.h>

namespace libre2d {

struct KeyFrame
{
	Mesh mesh;
	Vertex center;
	std::map<std::string, Vertex> anchors;

	void translateInPlace(const Vector &vec);
	void interpolateInPlace(const KeyFrame &other, float factor);
};

class Parameter
{
public:
	enum ParameterType {
		Discrete,
		Continuous
	};

	bool validate() const;
	KeyFrame setParameter(float param) const;

	std::string name;
	ParameterType type;
	float defaultValue;
	float min;
	float max;
	std::map<float, KeyFrame> keyFrames;
};

class Component
{
public:
	// render
	void setParameter(const std::string &paramName, float value);
	void setParameter(const std::map<std::string, float> &params);
	bool validate() const;

	std::string name;
	// uv map
	std::vector<Component *> children;
	std::map<std::string, Parameter> parameters;

	KeyFrame currentFrame;
};

} /* namespace libre2d */

#endif /* __LIBRE2D_COMPONENT_H__ */

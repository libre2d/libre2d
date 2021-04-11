/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * component.h - A container for a Component of a Model
 */

#ifndef __LIBRE2D_COMPONENT_H__
#define __LIBRE2D_COMPONENT_H__

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <libre2d/geometry.h>

namespace libre2d {

class Parameter
{
public:
	enum ParameterType {
		Discrete,
		Continuous
	};

	struct ParameterInfo {
		std::string name;
		ParameterType type;
		float defaultValue;
		float min;
		float max;
	};

	bool validate() const;
	Mesh setParameter(float param) const;

	std::shared_ptr<ParameterInfo> info;
	std::map<float, Mesh> keyMeshes;
};

class Component
{
public:
	static void init();

	// render
	void setParameters(const std::map<std::string, float> &params);
	void reset();
	bool validate() const;
	void render();

	std::string name;
	// uv map
	std::vector<Component> children;
	std::map<std::string, Parameter> parameters;

	Mesh currentMesh;

private:
	void moveChildren();
};

} /* namespace libre2d */

#endif /* __LIBRE2D_COMPONENT_H__ */

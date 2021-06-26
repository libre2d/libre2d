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
#include <libre2d/transformer.h>

namespace libre2d {

class Component
{
public:
	void setParameters(const std::map<std::string, float> &params);
	void reset();
	bool validate() const;
	void render(uint32_t programID, uint32_t textureID);

	std::string name;
	std::vector<UV> uvMap;
	std::vector<Component> children;
	std::vector<Transformer *> transformers;

	Mesh baseMesh;
	Mesh currentMesh;

private:
	void moveChildren();
};

} /* namespace libre2d */

#endif /* __LIBRE2D_COMPONENT_H__ */

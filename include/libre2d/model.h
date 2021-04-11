/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * model.h - The Libre2D model
 */

#ifndef __LIBRE2D_MODEL_H__
#define __LIBRE2D_MODEL_H__

#include <map>
#include <vector>

#include <libre2d/component.h>

namespace libre2d {

class Model
{
public:
	void setParameters(const std::map<std::string, float> &params);

	bool validate();

	void render();

	Component root;
	std::map<Parameter::ParameterInfo, std::vector<Parameter *>> parameters;
};

} /* namespace libre2d */

#endif /* __LIBRE2D_MODEL_H__ */

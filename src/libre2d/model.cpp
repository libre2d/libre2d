/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * model.cpp - The Libre2D model
 */

#include <libre2d/model.h>

#include <deque>

#include <libre2d/component.h>

/**
 * \file model.h
 * \brief The Libre2D model
 */

namespace libre2d {

/**
 * \class Model
 * \brief The Libre2D model
 *
 * This is the core class of Libre2D, and represents a 2D model. It
 * encapsulates a Component tree, and exposes Parameters. All Parameters
 * of the same ParameterInfo are grouped together so they can be manipulated
 * simultaneously.
 */

/**
 * \var Model::parameters
 * \brief All the parameters of the Component tree
 *
 * The key of this map is a ParameterInfo. These are the "originals", and all
 * info fields of the Parameter instances should point to this.
 *
 * The field is a vector of Parameter pointers. These should point to the
 * Parameter instances that are members of the Components.
 */

/**
 * \brief Set the parameters on the Model
 * \param[in] params Map of parameter name to parameter value
 *
 * This traverses the Component tree in a breadth-first manner and sets all the
 * parameters. The parameters are identified by name.
 */
void Model::setParameters(const std::map<std::string, float> &params)
{
	std::deque<Component *> queue;
	queue.push_back(&root);

	while (!queue.empty()) {
		Component *component = queue.front();
		queue.pop_front();

		for (Component &child : component->children)
			queue.push_back(&child);

		component->setParameters(params);
	}
}

/**
 * \brief Validate the Model
 *
 * Check that all Parameters in a Parameter vector have the same ParameterInfo
 *
 * \return true if the Model is valid, false otherwise
 */
bool Model::validate()
{
	bool valid = true;

	for (auto &pair : parameters) {
		for (Parameter *param : pair.second) {
			/* \todo confirm that this pointer comparison works */
			if (!param->info.get() ||
			    param->info.get() != &pair.first) {
				valid = false;
				break;
			}
		}
	}

	return valid;
}

} /* namespace libre2d */

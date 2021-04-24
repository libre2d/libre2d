/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * model.cpp - The Libre2D model
 */

#include <libre2d/model.h>

#include <libre2d/component.h>
#include <libre2d/utils.h>

#include <deque>
#include <tuple>

/**
 * \file model.h
 * \brief The Libre2D model
 */

namespace libre2d {

static std::string vertShaderCode_ =
"						\
#version 330\n					\
						\
layout (location = 0) in vec3 Position;		\
layout (location = 1) in vec2 iTexCoord;	\
						\
out vec2 oTexCoord;				\
						\
void main()					\
{						\
	gl_Position = vec4(Position, 1.0);	\
	oTexCoord = iTexCoord;			\
}						\
";

static std::string fragShaderCode_ =
"						\
#version 330\n					\
						\
in vec2 oTexCoord;				\
						\
out vec4 FragColor;				\
						\
uniform sampler2D sampler;			\
						\
void main()					\
{						\
	FragColor = texture(sampler, oTexCoord);\
}						\
";

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

static uint32_t programID_ = 0;

/*
 * \brief Initialize graphics
 *
 * This should be called after OpenGL is initialized
 */
void Model::init()
{
	programID_ = utils::gl::loadShadersFromStrings(
			vertShaderCode_.c_str(), 0,
			fragShaderCode_.c_str(), 0);
}

/*
 * \brief Load texture from image
 *
 * The Components will contain their own uv mapping, which contain coordinates
 * to this texture.
 *
 * This function is for bootstrapping, and will be replaced after a libre2d file
 * format and loader is created.
 * 
 * \return true on success, false on failure
 */
bool Model::loadTexture(const char *path)
{
	/*
	 * I think we can ignore width and height and number of color channels
	 * for now
	 */

	std::tie(textureID_, std::ignore, std::ignore, std::ignore) =
		utils::gl::loadTextureFromFile(path);

	return textureID_ != 0;
}

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

/**
 * \brief Render the Model to the default framebuffer
 *
 * Render the Components in the Component tree in bottom-up order
 *
 * \todo allow other framebuffers as parameters?
 */
void Model::render()
{
	std::deque<Component *> queue;
	queue.push_back(&root);

	while (!queue.empty()) {
		Component *component = queue.front();
		queue.pop_front();

		for (Component &child : component->children)
			queue.push_back(&child);

		component->render(programID_, textureID_);
	}
}

} /* namespace libre2d */

/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * model_loader.h - Save and load Models to and from files
 */

#include <libre2d/model_loader.h>

#include <libre2d/model.h>

/**
 * \file model_loader.h
 * \brief Save and load Models to and from files
 */

namespace libre2d {

/**
 * \class ModelLoader
 * \brief Save and load Models to and from files
 */

/**
 * \brief Load a Model from a file
 * \todo implement this
 */
Model ModelLoader::loadFromFile([[maybe_unused]] const std::string &filename)
{
	return Model();
}

/**
 * \brief Save a Model to a file
 * \todo implement this
 */
bool ModelLoader::saveToFile([[maybe_unused]] const std::string &filename,
			     [[maybe_unused]] Model &model)
{
	return true;
}

} /* namespace libre2d */

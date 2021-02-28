/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * model_loader.h - Save and load Models to and from files
 */

#ifndef __LIBRE2D_MODEL_LOADER_H__
#define __LIBRE2D_MODEL_LOADER_H__

#include <libre2d/model.h>

namespace libre2d {

class ModelLoader
{
	static Model loadFromFile(const std::string &filename);
	static bool saveToFile(const std::string &filename, Model &model);
};

} /* namespace libre2d */

#endif /* __LIBRE2D_MODEL_LOADER_H__ */

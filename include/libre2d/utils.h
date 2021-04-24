/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * utils.h - Utility functions
 */

#ifndef __LIBRE2D_UTILS_H__
#define __LIBRE2D_UTILS_H__

#include <string>
#include <tuple>

namespace libre2d {

namespace utils {

std::string loadFileToString(const char *path);

namespace gl {

bool compileShader(uint32_t shaderID, const std::string &source);

uint32_t loadShadersFromStrings(const char *vertSource, uint32_t vertShaderID,
				const char *fragSource, uint32_t fragShaderID);

uint32_t loadShaders(const char *vertexFilePath, const char *fragmentFilePath);

std::tuple<uint32_t, int, int, int> loadTextureFromFile(const char *filename);

} /* namespace gl */

} /* namespace utils */

} /* namespace libre2d */

#endif /* __LIBRE2D_MODEL_H__ */

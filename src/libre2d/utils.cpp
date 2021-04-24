/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * utils.cpp - Utility functions
 */

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <libre2d/internal/stb_image.h>

namespace libre2d {

namespace utils {

std::string loadFileToString(const char *path)
{
	std::stringstream sstr;

	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Failed to open file " << path << std::endl;
		return "";
	}

	sstr << file.rdbuf();
	file.close();

	return sstr.str();
}

namespace gl {

bool compileShader(uint32_t shaderID, const std::string &source)
{
	GLint ret = GL_FALSE;
	int infoLength;

	const char *sourceStr = source.c_str();
	glShaderSource(shaderID, 1, &sourceStr, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &ret);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLength);
	if (ret == GL_FALSE && infoLength > 0) {
		std::vector<char> errMsg(infoLength + 1);
		glGetShaderInfoLog(shaderID, infoLength, NULL, errMsg.data());
		std::string errStr(errMsg.begin(), errMsg.end());
		std::cerr << "Failed to compile shader: " << errStr << std::endl;
		return false;
	}

	return true;
}

uint32_t loadShadersFromStrings(const char *vertSource, uint32_t vertShaderID,
				const char *fragSource, uint32_t fragShaderID)
{
	GLuint vertexShaderID = vertShaderID ? vertShaderID :
					       glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = fragShaderID ? fragShaderID :
						 glCreateShader(GL_FRAGMENT_SHADER);

	if (!compileShader(vertexShaderID, vertSource))
		return 0;

	if (!compileShader(fragmentShaderID, fragSource))
		return 0;

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	GLint ret = GL_FALSE;
	int infoLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &ret);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLength);
	if (ret == GL_FALSE && infoLength > 0) {
		std::vector<char> errMsg(infoLength + 1);
		glGetProgramInfoLog(programID, infoLength, NULL, errMsg.data());
		std::string errStr(errMsg.begin(), errMsg.end());
		std::cerr << "Failed to link program: " << errStr << std::endl;
		return 0;
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	if (!vertShaderID)
		glDeleteShader(vertexShaderID);
	if (!fragShaderID)
		glDeleteShader(fragmentShaderID);

	return programID;
}

uint32_t loadShaders(const char *vertexFilePath, const char *fragmentFilePath)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertSource = loadFileToString(vertexFilePath);
	if (vertSource.empty())
		return 0;

	std::string fragSource = loadFileToString(fragmentFilePath);
	if (fragSource.empty())
		return 0;

	GLuint ret = loadShadersFromStrings(vertSource.c_str(), vertexShaderID,
					    fragSource.c_str(), fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return ret;
}

// texture, width, height, number of color channels
std::tuple<uint32_t, int, int, int> loadTextureFromFile(const char *path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	if (!textureID) {
		std::cerr << "Failed to generate texture" << std::endl;
		return { 0, 0, 0, 0 };
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 4);
	if (!data) {
		std::cerr << "Failed to load texture: " << path << std::endl;
		return { 0, 0, 0, 0 };
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		     GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return { textureID, width, height, nrChannels };
}

} /* namespace gl */

} /* namespace utils */

} /* namespace libre2d */

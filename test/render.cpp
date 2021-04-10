/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * render.cpp - Basic rendering test
 */

#include <libre2d/utils.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace libre2d;

GLuint programID_;

std::string vertShaderCode_ =
"						\
#version 330\n					\
						\
layout (location = 0) in vec3 Position;		\
						\
out vec4 Color;					\
						\
void main()					\
{						\
	gl_Position = vec4(Position, 1.0);	\
	Color = vec4(0.0, 0.5, 0.5, 1.0);	\
}						\
";

std::string fragShaderCode_ =
"						\
#version 330\n					\
						\
in vec4 Color;					\
						\
out vec4 FragColor;				\
						\
void main()					\
{						\
	FragColor = Color;			\
}						\
";

class Vector3f
{
public:
	Vector3f()
		: x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vector3f(float i, float j, float k)
		: x(i), y(j), z(k)
	{
	}

	float x;
	float y;
	float z;
};

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Vector3f vertices[] = {
		Vector3f(-1.0f, -1.0f, 0.0f),
		Vector3f( 1.0f, -1.0f, 0.0f),
		Vector3f( 0.0f,  1.0f, 0.0f),
	};

	unsigned int indices[] = {0, 1, 2};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glUseProgram(programID_);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("libre2d - render test");

	GLenum ret = glewInit();
	if (ret != GLEW_OK) {
		std::cerr << "Failed to initialize glew: "
			  << glewGetErrorString(ret) << std::endl;
		return -1;
	}

	programID_ = utils::gl::loadShadersFromStrings(vertShaderCode_.c_str(), 0,
						       fragShaderCode_.c_str(), 0);
	if (!programID_)
		return -1;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glutDisplayFunc(render);
	glutIdleFunc(render);

	glutMainLoop();
}

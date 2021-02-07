/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * geometry.h - Geometry-related structures
 */

#ifndef __LIBRE2D_GEOMETRY_H__
#define __LIBRE2D_GEOMETRY_H__

#include <cstdint>
#include <vector>

namespace libre2d {

class Vertex
{
public:
	constexpr Vertex()
		: x(0), y(0)
	{
	}

	constexpr Vertex(int32_t xpos, int32_t ypos)
		: x(xpos), y(ypos)
	{
	}

	int32_t x;
	int32_t y;

	void translate(int32_t dx, int32_t dy);
	void scale(const Vertex &origin, float mx, float my);
};

class Triangle
{
public:
	constexpr Triangle(Vertex &u1, Vertex &u2, Vertex &u3)
		: v1(u1), v2(u2), v3(u3)
	{
	}

	Vertex &v1;
	Vertex &v2;
	Vertex &v3;

	void translate(int32_t dx, int32_t dy);
	void scale(const Vertex &origin, float mx, float my);
};

class Mesh
{
	std::vector<Triangle> triangles;
};

} /* namespace libre2d */

#endif /* __LIBRE2D_GEOMETRY_H__ */

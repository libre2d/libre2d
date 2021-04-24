/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * geometry.h - Geometry-related structures
 */

#ifndef __LIBRE2D_GEOMETRY_H__
#define __LIBRE2D_GEOMETRY_H__

#include <array>
#include <cmath>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace libre2d {

const double PI = std::acos(-1);

class UV
{
public:
	constexpr UV()
		: u(0), v(0)
	{
	}

	constexpr UV(float upos, float vpos)
		: u(upos), v(vpos)
	{
	}

	float u;
	float v;
};

class Vertex
{
public:
	constexpr Vertex()
		: x(0), y(0), z(0)
	{
	}

	constexpr Vertex(float xpos, float ypos)
		: x(xpos), y(ypos), z(0)
	{
	}

	constexpr Vertex(float xpos, float ypos, float zpos)
		: x(xpos), y(ypos), z(zpos)
	{
	}

	float x;
	float y;
	float z;
};

typedef Vertex Vector;

class Mesh
{
public:
	Mesh() = default;
	Mesh(std::vector<Vertex> &vec);

	std::vector<Vertex> vertices;

	unsigned int center;
	std::map<std::string, unsigned int> anchors;
	std::vector<std::array<unsigned int, 3>> planes;

	const Vertex &centerVertex() const;
	const Vertex &anchorVertex(std::string componentName) const;

	Mesh scale(float factor, const Vertex &origin) const;
	void scaleInPlace(float factor, const Vertex &origin);

	Mesh translate(const Vector &vec) const;
	void translateInPlace(const Vector &vec);

	Mesh translateToPoint(const Vertex &dest) const;
	void translateToPointInPlace(const Vertex &dest);

	Mesh rotate(float degree, const Vertex &origin) const;
	void rotateInPlace(float degree, const Vertex &origin);

	Mesh interpolate(const Mesh &other, float factor) const;
	void interpolateInPlace(const Mesh &other, float factor);
};

} /* namespace libre2d */

#endif /* __LIBRE2D_GEOMETRY_H__ */

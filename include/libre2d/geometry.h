/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * geometry.h - Geometry-related structures
 */

#ifndef __LIBRE2D_GEOMETRY_H__
#define __LIBRE2D_GEOMETRY_H__

#include <cmath>
#include <cstdint>
#include <vector>

namespace libre2d {

const double PI = std::acos(-1);

class Vertex
{
public:
	constexpr Vertex()
		: x(0), y(0)
	{
	}

	constexpr Vertex(float xpos, float ypos)
		: x(xpos), y(ypos)
	{
	}

	float x;
	float y;
};

typedef Vertex Vector;

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
};

class Mesh
{
public:
	Mesh() = default;
	Mesh(std::vector<Vertex> &vec);

	std::vector<Vertex> vertices;
	Vertex center;

	Mesh scale(float factor, const Vertex &origin) const;
	void scaleInPlace(float factor, const Vertex &origin);

	Mesh translate(const Vector &vec) const;
	void translateInPlace(const Vector &vec);

	Mesh rotate(float degree, const Vertex &origin) const;
	void rotateInPlace(float degree, const Vertex &origin);

	Mesh interpolate(const Mesh &other, float factor) const;
	void interpolateInPlace(const Mesh &other, float factor);

private:
	Vertex calculateCenter(std::vector<Vertex> &vec);
};

} /* namespace libre2d */

#endif /* __LIBRE2D_GEOMETRY_H__ */

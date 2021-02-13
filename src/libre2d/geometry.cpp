/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * geometry.cpp - Geometry-related structures
 */

#include <libre2d/geometry.h>

#include <cmath>
#include <limits>

/**
 * \file geometry.h
 * \brief Data structures related to geometric objects
 */

namespace libre2d {

/*
 * \todo optimization?
 * \todo toString() ?
 */

/**
 * \class Vertex
 * \brief Describe a vertex in two-dimensional space
 *
 * The Vertex describes a point in two-dimensional space, with float
 * precision, and can be positive or negative.
 */

/**
 * \fn Vertex::Vertex()
 * \brief Construct a Vertex with x and y set to zero
 */

/**
 * \fn Vertex::Vertex(float xpos, float ypos)
 * \brief Construct a Vertex with given \a xpos and \a ypos values
 * \param[in] xpos The x coordinate
 * \param[in] ypos The y coordinate
 */

/**
 * \var Vertex::x
 * \brief The x coordinate of the Vertex
 */

/**
 * \var Vertex::y
 * \brief The y coordinate of the Vertex
 */


/**
 * \class Triangle
 * \brief Describe a triangle in two-dimensional space
 *
 * The Triangle describes a triangle in two-dimensional space, with float
 * precision.
 */

/**
 * \fn Triangle::Triangle(Vertex &u1, Vertex &u2, Vertex &u3)
 * \brief Construct a Triangle with given Vertices
 * \param[in] u1 The first Vertex
 * \param[in] u2 The second Vertex
 * \param[in] u3 The third Vertex
 * \todo Check if these vertices need to be in clockwise order
 */


/**
 * \class Mesh
 * \brief Describes an ordered set of vertices, and operations on the set
 *
 * The Mesh organizes a set of vertices into a Mesh, and defines
 * transformation operations on the set as a whole.
 */

/**
 * \var Mesh::vertices
 * \brief The set of vertices that the Mesh contains
 */

/**
 * \var Mesh::center
 * \brief The center vertex of the Mesh
 *
 * This vertex is calculated from the set of vertices, and is likely to not
 * be equal to any vertex in the set
 */

/**
 * \fn Mesh::Mesh()
 * \brief Construct a Mesh with no vertices and a center of zero
 */

/**
 * \brief Construct a Mesh from a set of vertices
 * \param[in] vec Vector of vertices
 *
 * This also automatically calculates and populates the center field. Note that
 * since Meshes are meant to have a rectangular bounding box, the center point
 * will simply be the center point of the bounding box of the mesh, and not the
 * point that is closest to all vertices.
 */
Mesh::Mesh(std::vector<Vertex> &vec)
{
	vertices = vec;
	center = calculateCenter(vec);
}

/**
 * \brief Calculate the center point from a set of vertices
 * \param[in] vec Vector of vertices
 * \return Center point, not necessarily a vertex from \a vec
 */
Vertex Mesh::calculateCenter(std::vector<Vertex> &vec)
{
	if (!vec.size())
		return Vertex();

	float min_x, min_y, max_x, max_y;
	min_x = min_y = std::numeric_limits<float>::max();
	max_x = max_y = std::numeric_limits<float>::min();

	for (Vertex &v : vec) {
		if (v.x > max_x)
			max_x = v.x;
		if (v.y > max_y)
			max_y = v.y;
		if (v.x < min_x)
			min_x = v.x;
		if (v.y < min_y)
			min_y = v.y;
	}

	return Vertex(min_x + ((max_x - min_x) / 2),
		      min_y + ((max_y - min_y) / 2));
}

void Mesh::scaleInPlace(float factor, const Vertex &origin)
{
	Vertex newOrigin = Vertex(
		((origin.x - center.x) * factor) + center.x,
		((origin.y - center.y) * factor) + center.y);

	for (Vertex &v : vertices) {
		v.x = ((v.x - center.x) * factor) + center.x;
		v.y = ((v.y - center.y) * factor) + center.y;
	}

	if (&origin == &center) {
		calculateCenter(vertices);
		return;
	}

	Vector translation = Vector(origin.x - newOrigin.x,
				    origin.y - newOrigin.y);
	/* This also recalculates center */
	translateInPlace(translation);
}

void Mesh::translateInPlace(const Vector &vec)
{
	for (Vertex &v : vertices) {
		v.x = v.x + vec.x;
		v.y = v.y + vec.y;
	}

	calculateCenter(vertices);
}

void Mesh::rotateInPlace(float degree, const Vertex &origin)
{
	float ox, oy;
	for (Vertex &v : vertices) {
		ox = v.x - origin.x;
		oy = v.y - origin.y;
		v.x = ox * cos(degree * PI / 180)
		      - oy * sin(degree * PI / 180)
		      + origin.x;
		v.y = ox * sin(degree * PI / 180)
		      + oy * cos(degree * PI / 180)
		      + origin.y;
	}

	if (&origin != &center)
		calculateCenter(vertices);
}

void Mesh::interpolateInPlace(const Mesh &other, float factor)
{
	size_t len = vertices.size();

	/* \todo Log error here */
	if (len != other.vertices.size())
		return;

	for (size_t i = 0; i < len; i++) {
		Vertex &v = vertices[i];
		const Vertex &o = other.vertices[i];

		v.x = (o.x - v.x) * factor + v.x;
		v.y = (o.y - v.y) * factor + v.y;
	}

	calculateCenter(vertices);
}

/**
 * \brief Scale the Mesh while keeping a constant point
 * \param[in] factor Scale factor
 * \param[in] origin The point to keep constant
 *
 * Scale the Mesh in both the X and Y dimensions equally, based on \a factor.
 * The scaling is done from the center of the Mesh, and \a origin is used
 * to keep that point in the Mesh constant.
 *
 * \return A new Mesh of this scaled by \a factor with \a origin constant
 */
Mesh Mesh::scale(float factor, const Vertex &origin) const
{
	Mesh mesh = *this;
	mesh.scaleInPlace(factor, origin);
	return mesh;
}

/**
 * \brief Translate the Mesh
 * \param[in] vec Translation vector
 * \return A new Mesh of this translated by \a vec
 */
Mesh Mesh::translate(const Vector &vec) const
{
	Mesh mesh = *this;
	mesh.translateInPlace(vec);
	return mesh;
}

/**
 * \brief Rotate the Mesh about an origin
 * \param[in] degree Counter-clockwise degrees through which to rotate the Mesh
 * \param[in] origin The origin about which to rotate the Mesh
 * \return A new rotated Mesh
 */
Mesh Mesh::rotate(float degree, const Vertex &origin) const
{
	Mesh mesh = *this;
	mesh.rotateInPlace(degree, origin);
	return mesh;
}

/**
 * \brief Interpolate between this Mesh and another Mesh with a factor
 * \param[in] other The other "endpoint" mesh
 * \param[in] factor The fraction to interpolate
 *
 * Create a new Mesh that is in between this Mesh and \a other by the
 * distance specified by \a factor. That is, if \a factor is 0, the new
 * Mesh will be equal to this, and if \a factor is 1, then the new Mesh
 * will be equal to \a other.
 *
 * \return A new mesh interpolated between this and \a other
 */
Mesh Mesh::interpolate(const Mesh &other, float factor) const
{
	Mesh mesh = *this;
	mesh.interpolateInPlace(other, factor);
	return mesh;
}

} /* namespace libre2d */

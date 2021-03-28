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
 *
 * There is a z value, but that is only used for z-indexing, and not for 3D
 * space.
 */

/**
 * \fn Vertex::Vertex()
 * \brief Construct a Vertex with x and y and z-index set to zero
 */

/**
 * \fn Vertex::Vertex(float xpos, float ypos)
 * \brief Construct a Vertex with given \a xpos and \a ypos, with z set to zero
 * \param[in] xpos The x coordinate
 * \param[in] ypos The y coordinate
 */

/**
 * \fn Vertex::Vertex(float xpos, float ypos, float zpos)
 * \brief Construct a Vertex with given \a xpos, \a ypos, and \a zpos values
 * \param[in] xpos The x coordinate
 * \param[in] ypos The y coordinate
 * \param[in] zpos The z coordinate
 */

/**
 * \var Vertex::x
 * \brief The x coordinate of the Vertex
 */

/**
 * \var Vertex::y
 * \brief The y coordinate of the Vertex
 */

/*
 * \var Vertex::z
 * \brief The z-index of the Vertex
 */

void Vertex::interpolateInPlace(const Vertex &other, float factor)
{
	x = (other.x - x) * factor + x;
	y = (other.y - y) * factor + y;
	z = (other.z - z) * factor + z;
}

Vertex Vertex::interpolate(const Vertex &other, float factor) const
{
	Vertex vertex = *this;
	vertex.interpolateInPlace(other, factor);
	return vertex;
}

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
 * This is an index into the vertices array to designate the vertex that is the
 * origin of transformation. This is the vertex that will serve as the center
 * point for scale and rotate operations.
 */

/**
 * \var Mesh::anchors
 * \brief Map of Component name to anchor point
 *
 * The key to this map is a Component name, and the value is an index into the
 * vertices array to designate the anchor point corresponding to the Component.
 * This anchor point will used to translate the Component's final mesh using
 * its center point. The Component shall be a child of the Component that owns
 * this Mesh.
 */

const Vertex &Mesh::centerVertex() const
{
	return vertices.at(center);
}

const Vertex &Mesh::anchorVertex(std::string componentName) const
{
	return vertices.at(anchors.at(componentName));
}

/**
 * \var Mesh::planes
 * \brief The set of triangles
 *
 * This is a vector of triangles, where the triangles are defined by indexes
 * into the vertices array.
 */

/**
 * \fn Mesh::Mesh()
 * \brief Construct a Mesh with no vertices and a center of zero
 */

/**
 * \brief Construct a Mesh from a set of vertices
 * \param[in] vec Vector of vertices
 */
Mesh::Mesh(std::vector<Vertex> &vec)
{
	vertices = vec;
}

void Mesh::scaleInPlace(float factor, const Vertex &origin)
{
	Vertex &centerV = vertices.at(center);

	Vertex newOrigin = Vertex(
		((origin.x - centerV.x) * factor) + centerV.x,
		((origin.y - centerV.y) * factor) + centerV.y);

	for (Vertex &v : vertices) {
		v.x = ((v.x - centerV.x) * factor) + centerV.x;
		v.y = ((v.y - centerV.y) * factor) + centerV.y;
	}

	Vector translation = Vector(origin.x - newOrigin.x,
				    origin.y - newOrigin.y);
	translateInPlace(translation);
}

void Mesh::translateInPlace(const Vector &vec)
{
	for (Vertex &v : vertices) {
		v.x = v.x + vec.x;
		v.y = v.y + vec.y;
		v.z = v.z + vec.z;
	}
}

void Mesh::translateToPointInPlace(const Vertex &dest)
{
	Vertex &centerV = vertices.at(center);

	Vector transVec(dest.x - centerV.x,
			dest.y - centerV.y,
			dest.z - centerV.z);
	translateInPlace(transVec);
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
		v.z = (o.z - v.z) * factor + v.z;
	}
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
 * This operation ignores the z-index.
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
 * \brief Translate the Mesh to a destination point
 * \param[in] dest Destination coordinate
 * \return A new Mesh of this translated to \a dest
 */
Mesh Mesh::translateToPoint(const Vertex &dest) const
{
	Mesh mesh = *this;
	mesh.translateToPointInPlace(dest);
	return mesh;
}

/**
 * \brief Rotate the Mesh about an origin
 * \param[in] degree Counter-clockwise degrees through which to rotate the Mesh
 * \param[in] origin The origin about which to rotate the Mesh
 *
 * This operation ignores the z-index.
 *
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

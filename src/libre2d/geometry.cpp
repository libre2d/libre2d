/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * geometry.cpp - Geometry-related structures
 */

#include <libre2d/geometry.h>

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
 * The Vertex describes a point in two-dimensional space, with integral
 * precision, and can be positive or negative.
 */

/**
 * \fn Vertex::Vertex()
 * \brief Construct a Vertex with x and y set to zero
 */

/**
 * \fn Vertex::Vertex(int32_t xpos, int ypos)
 * \brief Construct a Vertex with given \a xpos and \a ypos values
 * \param[in] xpos The x coordinate
 * \param[in] ypos The y coordinate
 */

/**
 * \var Vertex::x
 * \brief the x coordinate of the Vertex
 */

/**
 * \var Vertex::y
 * \brief The y coordinate of the Vertex
 */

/**
 * \brief Apply a translation on the Vertex
 * \param[in] dx The x component of the two-dimensional translation vector
 * \param[in] dy the y component of the two-dimensional translation vector
 */
void Vertex::translate(int32_t dx, int32_t dy)
{
	x += dx;
	y += dy;
}

/**
 * \brief Apply a scale on the Vertex
 * \param[in] origin The Vertex to serve as the origin of the scaling operation
 * \param[in] mx The x component of the two-dimensional scale multiplier vector
 * \param[in] my the y component of the two-dimensional scale multiplier vector
 */
void Vertex::scale(const Vertex &origin, float mx, float my)
{
	x = (x - origin.x) * mx + origin.x;
	y = (y - origin.y) * my + origin.y;
}

/**
 * \class Triangle
 * \brief Describe a triangle in two-dimensional space
 *
 * The Triangle describes a triangle in two-dimensional space, with integral
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
 * \brief Apply a translation on the Triangle
 * \param[in] dx The x component of the two-dimensional translation vector
 * \param[in] dy the y component of the two-dimensional translation vector
 */
void Triangle::translate(int32_t dx, int32_t dy)
{
	v1.translate(dx, dy);
	v2.translate(dx, dy);
	v3.translate(dx, dy);
}

/**
 * \brief Apply a scale on the Triangle
 * \param[in] origin The Vertex to serve as the origin of the scaling operation
 * \param[in] mx The x component of the two-dimensional scale multiplier vector
 * \param[in] my the y component of the two-dimensional scale multiplier vector
 */
void Triangle::scale(const Vertex &origin, float mx, float my)
{
	v1.scale(origin, mx, my);
	v2.scale(origin, mx, my);
	v3.scale(origin, mx, my);
}

} /* namespace libre2d */

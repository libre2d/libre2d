/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * component.cpp - A container for a Component of a Model
 */

#include <libre2d/component.h>

#include <GL/glew.h>

#include <iostream>
#include <map>

/**
 * \file component.h
 * \brief Data structures related to a Component of a Model
 */

namespace libre2d {

/**
 * \class Component
 * \brief Describes a Component of a Model
 *
 * A Component is a grouping of a mesh, uv-mapping, parameters, and children
 * Components. In the example of a Model of a humanoid face, a Component might
 * describe a blank face, and there would be different children Components to
 * describe each eye, nose, mouth, etc.
 *
 * The mesh of the Component describes the current Mesh that the Component
 * is taking. The Parameters contain the necessary information for transforming
 * the current mesh. The position of children Components are mapped using the
 * anchor points of the parent Component, and the transformation center point
 * of the child Component.
 *
 * \todo finish the documentation
 * \todo implement validate
 */

bool Component::validate() const
{
	/*
	 * \todo validate the length of the children list with the anchor list
	 * length of the KeyFrames in the Parameters
	 * length of vertices in the meshes (recurse into parameter validation?)
	 * length of uvMap vs number of vertices in the meshes
	 */
	return true;
}

/**
 * \brief Reset the current mesh of the Component to the base Mesh
 *
 * This preserves the center point position (as a parent might have translated
 * it via anchor points).
 */
void Component::reset()
{
	Vertex origin = currentMesh.centerVertex();

	currentMesh = baseMesh;
	currentMesh.translateToPointInPlace(origin);

	moveChildren();
}

/**
 * \brief Set the parameters on the current Component
 * \param[in] inputParams Map of parameter name to parameter value
 *
 * This also moves the children after the anchors are moved
 */
void Component::setParameters(const std::map<std::string, float> &inputParams)
{
	reset();

	bool first = true;

	for (Transformer *transformer : transformers) {
		auto inputParam = inputParams.find(transformer->info->name);

		currentMesh = transformer->transform(first ? baseMesh : currentMesh,
						     inputParam == inputParams.end() ?
						     transformer->currentValue :
						     inputParam->second);

		first = false;
	}

	moveChildren();
}

/**
 * \brief Render the Component to the default framebuffer
 */
void Component::render(uint32_t programID, uint32_t textureID)
{
	unsigned int vertSize = currentMesh.vertices.size() * sizeof(Vertex);
	unsigned int indexSize = currentMesh.planes.size() *
				 3 * sizeof(unsigned int);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	unsigned int cbo;
	glGenBuffers(1, &cbo);
	glBindBuffer(GL_ARRAY_BUFFER, cbo);
	glBufferData(GL_ARRAY_BUFFER, uvMap.size() * sizeof(UV),
		     uvMap.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertSize,
		     currentMesh.vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize,
		     currentMesh.planes.data(), GL_STATIC_DRAW);

	glUseProgram(programID);

	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &cbo);
}

/**
 * \brief Move the children Components to match the anchors
 *
 * This should be called after any transformation is made to the currentMesh
 */
void Component::moveChildren()
{
	for (Component &child : children) {
		const Vertex &anchor = currentMesh.anchorVertex(child.name);
		child.currentMesh.translateToPointInPlace(anchor);
	}
}

} /* namespace libre2d */

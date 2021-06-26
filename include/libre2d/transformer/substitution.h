/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * substitution.h - A mesh substitution transformer
 */

#ifndef __LIBRE2D_TRANSFORMER_SUBSTITUTION_H__
#define __LIBRE2D_TRANSFORMER_SUBSTITUTION_H__

#include <map>

#include <libre2d/geometry.h>
#include <libre2d/transformer.h>

namespace libre2d {

class TransformerSubstitution : public Transformer
{
public:
	~TransformerSubstitution() { }

	Mesh transform(const Mesh &mesh, float param) const;

	std::map<float, Mesh> keyMeshes;
};

} /* namespace libre2d */

#endif /* __LIBRE2D_TRANSFORMER_SUBSTITUTION_H__ */

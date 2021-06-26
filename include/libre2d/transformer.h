/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * transformer.h - A transformer for transforming a Component's mesh
 */

#ifndef __LIBRE2D_TRANSFORMER_H__
#define __LIBRE2D_TRANSFORMER_H__

#include <memory>
#include <string>

#include <libre2d/geometry.h>

namespace libre2d {

class Transformer
{
public:
	virtual ~Transformer() = 0;

	enum ParameterType {
		Discrete,
		Continuous
	};

	struct ParameterInfo {
		std::string name;
		ParameterType type;
		float defaultValue;
		float min;
		float max;
	};

	bool validate() const;
	virtual Mesh transform(const Mesh &mesh, float param) const = 0;

	std::shared_ptr<ParameterInfo> info;
	float currentValue;
};

} /* namespace libre2d */

#endif /* __LIBRE2D_TRANSFORMER_H__ */

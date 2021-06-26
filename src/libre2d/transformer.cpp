/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * Copyright (C) 2021, Paul Elder
 *
 * transformer.cpp - A transformer for transforming a Component's mesh
 */

#include <libre2d/transformer.h>

#include <iostream>

/**
 * \file transformer.h
 * \brief Data structures related to Transformers
 */

namespace libre2d {

/**
 * \class Transformer
 * \brief Implements a transformation function that can transform a mesh
 *
 * \todo document the enum
 * \todo cache previous setParameter() results
 * \todo finish the documentation
 * \todo set up logging
 */

/**
 * \var ParameterInfo::name
 * \brief The name of the parameter
 *
 * This is used to link with other parameters in the Model
 */

/**
 * \var ParameterInfo::type
 * \brief The type of the parameter, either disrete or continuous
 */

/**
 * \var ParameterInfo::min
 * \brief The minimum value of the parameter
 */

/**
 * \var ParameterInfo::max
 * \brief The maximum value of the parameter
 */

Transformer::~Transformer()
{
}

bool Transformer::validate() const
{
	bool valid = true;

	if (info->min > info->max) {
		std::cerr << "ERROR Parameter: min is greater than max" << std::endl;
		valid = false;
	}

	/* \todo check the number of vertices in all meshes and all anchor lists */

	return valid;
}

} /* namespace libre2d */

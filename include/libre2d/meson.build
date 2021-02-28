# SPDX-License-Identifier: CC0-1.0

libre2d_public_headers = files([
    'component.h',
    'geometry.h',
    'model.h',
    'model_loader.h',
])

include_dir = join_paths(libre2d_include_dir, 'libre2d')

subdir('internal')

install_headers(libre2d_public_headers,
                subdir : include_dir)

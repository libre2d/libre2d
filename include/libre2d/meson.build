# SPDX-License-Identifier: CC0-1.0

libre2d_public_headers = files([
    'buffer.h',
    'component.h',
    'geometry.h',
    'model.h',
    'model_loader.h',
    'transformer.h',
    'utils.h',
])

include_dir = join_paths(libre2d_include_dir, 'libre2d')

subdir('internal')
subdir('transformer')

install_headers(libre2d_public_headers,
                subdir : include_dir)

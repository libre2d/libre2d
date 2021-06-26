# SPDX-License-Identifier: CC0-1.0

libre2d_sources = files([
    'component.cpp',
    'geometry.cpp',
    'model.cpp',
    'model_loader.cpp',
    'transformer.cpp',
    'utils.cpp',
])

libre2d_sources += libre2d_public_headers
libre2d_sources += libre2d_internal_headers

includes = [
    libre2d_includes,
]

subdir('transformer')

libgl = dependency('gl')
libglew = dependency('glew')

libre2d_deps = [
    libgl,
    libglew,
]

libre2d = shared_library('libre2d',
                         libre2d_sources,
                         install : true,
                         include_directories : includes,
                         dependencies : libre2d_deps)

libre2d_dep = declare_dependency(sources : [
                                     libre2d_public_headers,
                                 ],
                                 include_directories : libre2d_includes,
                                 link_with : libre2d)

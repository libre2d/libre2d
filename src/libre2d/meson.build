# SPDX-License-Identifier: CC0-1.0

libre2d_sources = files([
    'component.cpp',
    'geometry.cpp',
    'model.cpp',
    'model_loader.cpp',
])

libre2d_sources += libre2d_public_headers

includes = [
    libre2d_includes,
]

libre2d = shared_library('libre2d',
                         libre2d_sources,
                         install : true,
                         include_directories : includes)

libre2d_dep = declare_dependency(sources : [
                                     libre2d_public_headers,
                                 ],
                                 include_directories : libre2d_includes,
                                 link_with : libre2d)

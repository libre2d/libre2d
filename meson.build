# SPDX-License-Identifier: CC0-1.0

project('libre2d', 'c', 'cpp',
    meson_version : '>= 0.53',
    version : '0.0.0',
    default_options: [
        'werror=true',
        'warning_level=2',
        'cpp_std=c++17',
    ],
    license : 'LGPL 2.1+')

cc = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')
config_h = configuration_data()

common_arguments = [
    '-Wshadow',
    '-include', 'config.h',
]

c_arguments = common_arguments
cpp_arguments = common_arguments

add_project_arguments(c_arguments, language : 'c')
add_project_arguments(cpp_arguments, language : 'cpp')
add_project_link_arguments(cpp_arguments, language : 'cpp')

libre2d_includes = include_directories('include')

subdir('include')
subdir('src')

# TODO Documentation

subdir('test')

configure_file(output : 'config.h', configuration : config_h)

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : libre2d,
                 version : '1.0',
                 name : 'libre2d',
                 description : 'Libre2D Library',
                 subdirs : 'libre2d')

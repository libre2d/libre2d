# SPDX-License-Identifier: CC0-1.0

qauctor_sources = files([
    'main.cpp',
    'main_window.cpp',
    'canvas.cpp',
])

qauctor_moc_headers = files([
    'main_window.h',
    'canvas.h',
])

qauctor_resources = files([
])

qt5 = import('qt5')
qt5_dep = dependency('qt5',
                     method : 'pkg-config',
                     modules : ['Core', 'Gui', 'Widgets'],
                     required : get_option('editor'),
                     version : '>= 5.4')

if qt5_dep.found()
    qauctor_deps = [
        libre2d_dep,
        qt5_dep,
    ]

    qt5_cpp_args = [ '-DQT_NO_KEYWORDS' ]

    resources = qt5.preprocess(moc_headers : qauctor_moc_headers,
                               qresources : qauctor_resources,
                               dependencies : qt5_dep)

    qauctor = executable('qauctor', qauctor_sources, resources,
                                install : true,
                                dependencies : qauctor_deps,
                                cpp_args : qt5_cpp_args)
endif

# SPDX-License-Identifier: CC0-1.0

libre2d_editor_sources = files([
])

libre2d_editor_moc_headers = files([
])

libre2d_editor_resources = files([
])

qt5 = import('qt5')
qt5_dep = dependency('qt5',
                     method : 'pkg-config',
                     modules : ['Core', 'Gui', 'Widgets'],
                     required : get_option('editor'),
                     version : '>= 5.4')

if qt5_dep.found()
    libre2d_editor_deps = [
        libre2d_dep,
        qt5_dep,
    ]

    qt5_cpp_args = [ '-DQT_NO_KEYWORDS' ]

    resources = qt5.preprocess(moc_headers : libre2d_editor_moc_headers,
                               qresources : libre2d_editor_resources,
                               dependencies : qt5_dep)

    libre2d_editor = executable('libre2d_editor', libre2d_editor_sources, resources,
                                install : true,
                                dependencies : libre2d_editor_deps,
                                cpp_args : qt5_cpp_args)
endif

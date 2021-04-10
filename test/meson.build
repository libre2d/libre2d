# SPDX-License-Identifier: CC0-1.0

public_tests = [
]

internal_tests = [
]

public_test_deps = [
    cc.find_library('glut'),
]

foreach t: public_tests
    exe = executable(t[0], t[1],
                     dependencies : [libre2d_dep,
                                     libre2d_deps,
                                     public_test_deps])
    test(t[0], exe)
endforeach

foreach t : internal_tests
    exe = executable(t[0], t[1],
                     dependencies : libre2d_dep)

    test(t[0], exe)
endforeach

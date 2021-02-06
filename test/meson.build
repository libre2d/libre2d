# SPDX-License-Identifier: CC0-1.0

public_tests = [
]

internal_tests = [
]

foreach t: public_tests
    exe = executable(t[0], t[1],
                     dependencies : libre2d_dep)
    test(t[0], exe)
endforeach

foreach t : internal_tests
    exe = executable(t[0], t[1],
                     dependencies : libre2d_dep)

    test(t[0], exe)
endforeach

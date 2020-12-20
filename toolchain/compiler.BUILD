# toolchain/compiler.BUILD

package(default_visibility = ['//visibility:public'])

# Some targets may need to directly depend on these files.
exports_files(glob(["bin/*", "lib/*"]))

filegroup(
    name = "empty",
    srcs = [],
)

## LLVM toolchain files

filegroup(
    name = "clang",
    srcs = [
        "bin/clang",
        "bin/clang++",
        "bin/clang-cpp",
    ],
)

filegroup(
    name = "ld",
    srcs = [
        "bin/ld.lld",
        "bin/ld",
        "bin/ld.gold",  # Dummy file on non-linux.
    ],
)

filegroup(
    name = "include",
    srcs = glob([
        "include/c++/**",
        "lib/clang/11.0.0/include/**",
    ]),
)

filegroup(
    name = "lib",
    srcs = glob(
        [
            "lib/lib*.a",
            "lib/clang/11.0.0/lib/**/*.a",
        ],
        exclude = [
            "lib/libLLVM*.a",
            "lib/libclang*.a",
            "lib/liblld*.a",
        ],
    ),
)

filegroup(
    name = "compiler_components",
    srcs = [
        ":clang",
        ":include",
        ":sysroot_components",
    ],
)

filegroup(
    name = "ar",
    srcs = ["bin/llvm-ar"],
)

filegroup(
    name = "as",
    srcs = [
        "bin/clang",
        "bin/llvm-as",
    ],
)

filegroup(
    name = "nm",
    srcs = ["bin/llvm-nm"],
)

filegroup(
    name = "objcopy",
    srcs = ["bin/llvm-objcopy"],
)

filegroup(
    name = "objdump",
    srcs = ["bin/llvm-objdump"],
)

filegroup(
    name = "profdata",
    srcs = ["bin/llvm-profdata"],
)

filegroup(
    name = "dwp",
    srcs = ["bin/llvm-dwp"],
)

filegroup(
    name = "ranlib",
    srcs = ["bin/llvm-ranlib"],
)

filegroup(
    name = "readelf",
    srcs = ["bin/llvm-readelf"],
)

filegroup(
    name = "binutils_components",
    srcs = glob(["bin/*"]),
)

filegroup(
    name = "linker_components",
    srcs = [
        ":clang",
        ":ld",
        ":ar",
        ":lib",
        ":sysroot_components",
    ],
)

filegroup(
    name = "all_components",
    srcs = [
        ":binutils_components",
        ":compiler_components",
        ":linker_components",
    ],
)

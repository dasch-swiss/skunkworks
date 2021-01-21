#
# this build file is used directly in the workspace
#

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "fmt",
    srcs = [
        "src/format.cc",
        "src/os.cc",
    ],
    hdrs = [
        "include/fmt/chrono.h",
        "include/fmt/color.h",
        "include/fmt/core.h",
        "include/fmt/format-inl.h",
        "include/fmt/format.h",
        "include/fmt/locale.h",
        "include/fmt/os.h",
        "include/fmt/ostream.h",
        "include/fmt/posix.h",
        "include/fmt/printf.h",
        "include/fmt/ranges.h",
    ],
    #copts = ["-Iexternal/fmt/include"],
    #include_prefix = "fmt",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

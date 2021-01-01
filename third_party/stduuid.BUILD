#
# this build file is used directly in the workspace
#
# to use, set dependency to @stduuid//:stduuid

load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "stduuid",
    deps = [
        ":uuid",
        ":gsl",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "uuid",
    hdrs = [
        "include/uuid.h",
    ],
    include_prefix = "external/stduuid/include",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "gsl",
    hdrs = [
        "gsl/gsl",
        "gsl/gsl_algorithm",
        "gsl/gsl_assert",
        "gsl/gsl_byte",
        "gsl/gsl_util",
        "gsl/multi_span",
        "gsl/pointers",
        "gsl/span",
        "gsl/string_span",
    ],
    include_prefix = "external/stduuid/gsl",
    strip_include_prefix = "gsl",
    visibility = ["//visibility:public"],
)

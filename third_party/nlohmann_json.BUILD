#
# this build file is used directly in the workspace
#
# to use, set dependency to @nlohmann//:nlohmann

load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "nlohmann",
    hdrs = [
       "single_include/nlohmann/json.hpp",
    ],
    include_prefix = "external",
    strip_include_prefix = "single_include",
    visibility = ["//visibility:public"],
)

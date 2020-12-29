#
# this build file is used directly in the workspace
#
# to use, set dependency to @stduuid//:stduuid

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "stduuid",
    hdrs = [
       "include/uuid.h",
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
    copts = ["-Iexternal/stduuid/gsl"],
    visibility = ["//visibility:public"],
)

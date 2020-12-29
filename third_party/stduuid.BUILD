#
# this build file is used directly in the workspace
#
# to use, set dependency to @stduuid//:stduuid

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "stduuid",
    hdrs = glob([
       "include/*.h",
       "gls/*"
   ]),
    copts = ["-Iexternal/stduuid/gsl"],
)
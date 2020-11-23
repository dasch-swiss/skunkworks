#
# this build file is used directly in the workspace
#

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "sqlite3",
    srcs = glob(
        include = [
            "*.c",
            "*.h",
        ]
    ),
    hdrs = [
        "sqlite3.h",
        "sqlite3ext.h",
    ],
    visibility = ["//visibility:public"],
)

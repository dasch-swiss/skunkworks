# Description:
#   Build rule for Lua 5.1: copied from https://github.com/deepmind/lab/blob/master/bazel/lua.BUILD

# this build file is used directly in the workspace

cc_library(
    name = "lua",
    srcs = glob(
        include = [
            "*.c",
            "*.h",
        ],
        exclude = [
            "lauxlib.h",
            "lua.c",
            "lua.h",
            "lua.hpp",
            "luac.c",
            "lualib.h",
            "print.c",
        ],
    ),
    hdrs = [
        "lauxlib.h",
        "lua.h",
        "lualib.h",
        "lua.hpp",
    ],
    visibility = ["//visibility:public"],
)

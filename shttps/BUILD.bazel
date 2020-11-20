package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "main",
    srcs = ["src/shttps.cpp"],
    deps = [
        ":shttps-lib",
        "//ext:jwt",
        "//ext:sole",
        "//ext:jansson",
        "@lua//:lua",
        "//ext:openssl",
    ],
)

cc_library(
    name = "shttps-lib",
    srcs = [
        "src/ChunkReader.cpp",
        "src/Connection.cpp",
        "src/Error.cpp",
        "src/Hash.cpp",
        "src/LuaServer.cpp",
        "src/LuaSqlite.cpp",
        "src/Parsing.cpp",
        "src/Server.cpp",
        "src/SockStream.cpp",
    ],
    hdrs = [
        "include/shttps/ChunkReader.h",
        "include/shttps/Connection.h",
        "include/shttps/Error.h",
        "include/shttps/Global.h",
        "include/shttps/Hash.h",
        "include/shttps/LuaServer.h",
        "include/shttps/LuaSqlite.h",
        "include/shttps/makeunique.h",
        "include/shttps/Parsing.h",
        "include/shttps/Server.h",
        "include/shttps/SockStream.h",
    ],
    includes = ["include"],
    deps = [
        "//ext:openssl",
        "//ext:file"
    ]
)
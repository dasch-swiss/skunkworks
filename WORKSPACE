workspace(name = "swiss_dasch_skunkworks")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# The rules_foreign_cc rule repository
http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-master",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

# Register default toolchain. It is also possible to register
# custom toolchains.
rules_foreign_cc_dependencies(register_default_tools = True)


# @zlib//:all
http_archive(
    name = "zlib",
    build_file_content = all_content,
    strip_prefix = "zlib-1.2.11",
    urls = ["https://zlib.net/zlib-1.2.11.tar.gz"],
    sha256 = "c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1",
)


# @openssl//:all
http_archive(
    name = "openssl",
    build_file_content = all_content,
    strip_prefix = "openssl-OpenSSL_1_1_1d",
    urls = ["https://github.com/openssl/openssl/archive/OpenSSL_1_1_1d.tar.gz"],
    sha256 = "23011a5cc78e53d0dc98dfa608c51e72bcd350aa57df74c5d5574ba4ffb62e74"
)


# @lua//:all
http_archive(
    name = "lua",
    build_file = "@//ext:lua.BUILD",
    #build_file_content = all_content,
    strip_prefix = "lua-5.3.5/src",
    urls = ["https://www.lua.org/ftp/lua-5.3.5.tar.gz"],
    sha256 = "0c2eed3f960446e1a3e4b9a1ca2f3ff893b6ce41942cf54d5dd59ab4b3b058ac",
)


# @jansson//:all
http_archive(
    name = "jansson",
    build_file_content = all_content,
    strip_prefix = "jansson-2.12",
    urls = ["https://github.com/akheron/jansson/archive/v2.12.tar.gz"],
    sha256 = "76260d30e9bbd0ef392798525e8cd7fe59a6450c54ca6135672e3cd6a1642941",
)

# @sqlite//:all
http_archive(
    name = "sqlite3",
    build_file_content = all_content,
    strip_prefix = "sqlite-autoconf-3300100",
    urls = ["https://www.sqlite.org/2019/sqlite-autoconf-3300100.tar.gz"],
    sha256 = "8c5a50db089bd2a1b08dbc5b00d2027602ca7ff238ba7658fabca454d4298e60",
)

# google test
git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    tag = "release-1.10.0",
)

all_and_magic_files = """
filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])
filegroup(name = "magic_files", srcs = glob(["magic/Magdir/**"]), visibility = ["//visibility:public"])
"""

# file aka libmagic
http_archive(
    name = "file",
    build_file_content = all_and_magic_files,
    strip_prefix = "file-5.37",
    urls = ["https://astron.com/pub/file/file-5.37.tar.gz"],
    # sha256 = "8c5a50db089bd2a1b08dbc5b00d2027602ca7ff238ba7658fabca454d4298e60",
)

workspace(name = "swiss_dasch_skunkworks")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Get rules_cc. Although the cc rules are built into Bazel, they will be moved
# out in the future, into their own rules. Using this now, will save migration work later.
rules_cc_tag = "b1c40e1de81913a3c40e5948f78719c28152486d" # 11. November 2020
rules_cc_sha256 = "d0c573b94a6ef20ef6ff20154a23d0efcb409fb0e1ff0979cec318dfe42f0cdd"
http_archive(
    name = "rules_cc",
    strip_prefix = "rules_cc-{}".format(rules_cc_tag),
    url = "https://github.com/bazelbuild/rules_cc/archive/{}.zip".format(rules_cc_tag),
    sha256 = rules_cc_sha256,
)

## Get rule that allows us to use official clang binaries.
#grail_tag = "0.5.7" # 5. November 2020
#grail_sha256 = "83f691deff0f131b6d40587f07361cb25dad4a66e5ed8988cbcee78ebfe3d5cd"
#http_archive(
#    name = "com_grail_bazel_toolchain",
#    strip_prefix = "bazel-toolchain-{}".format(grail_tag),
#    url = "https://github.com/grailbio/bazel-toolchain/archive/{}.zip".format(grail_tag),
#    sha256 = grail_sha256
#)
#
#load("@com_grail_bazel_toolchain//toolchain:deps.bzl", "bazel_toolchain_dependencies")
#
#bazel_toolchain_dependencies()
#
#load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")
#
#llvm_toolchain(
#    name = "llvm_toolchain",
#    llvm_version = "11.0.0",
#)
#
#register_toolchains(
#    "@llvm_toolchain//:cc-toolchain-linux",
#)

# The rules_foreign_cc rule repository - commit from 26.10.2020
rules_foreign_cc_version = "d54c78ab86b40770ee19f0949db9d74a831ab9f0"
rules_foreign_cc_version_sha256 = "3c6445404e9e5d17fa0ecdef61be00dd93b20222c11f45e146a98c0a3f67defa"
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-%s" % rules_foreign_cc_version,
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/%s.zip" % rules_foreign_cc_version,
    sha256 = rules_foreign_cc_version_sha256,
)
# Recursively import Nixpkgs rules' dependencies and register default tools-toolchains (make, cmake, ninja).
load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies(register_default_tools = True)

# used as default build file content in the download rules used in combination with rules_foreign_cc
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

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
    strip_prefix = "openssl-OpenSSL_1_1_1g",
    urls = ["https://github.com/openssl/openssl/archive/OpenSSL_1_1_1g.tar.gz"],
    sha256 = "281e4f13142b53657bd154481e18195b2d477572fdffa8ed1065f73ef5a19777"
)

# @lua_archive//:lua
http_archive(
    name = "lua",
    build_file = "@//third_party:lua.BUILD",
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

# @sqlite3//:sqlite3
http_archive(
    name = "sqlite3",
    build_file = "@//third_party:sqlite3.BUILD",
    strip_prefix = "sqlite-amalgamation-3330000",
    urls = ["https://www.sqlite.org/2020/sqlite-amalgamation-3330000.zip"],
    sha256 = "b34f4c0c0eefad9a7e515c030c18702e477f4ef7d8ade6142bdab8011b487ac6",
)

# google test
# to use, set dependency to @gtest//:main
http_archive(
    name = "gtest",
    build_file = "@//third_party:gtest.BUILD",
    strip_prefix = "googletest-release-1.10.0/googletest",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
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
    sha256 = "e9c13967f7dd339a3c241b7710ba093560b9a33013491318e88e6b8b57bae07f",
)

# curl
http_archive(
    name = "curl",
    build_file_content = all_and_magic_files,
    strip_prefix = "curl-7.70.0",
    urls = ["https://curl.haxx.se/download/curl-7.70.0.tar.gz"],
    sha256 = "ca2feeb8ef13368ce5d5e5849a5fd5e2dd4755fecf7d8f0cc94000a4206fb8e7",
)

# catch2
catch2_tag = "2.13.3"
catch2_sha256 = "1804feb72bc15c0856b4a43aa586c661af9c3685a75973b6a8fc0b950c7cfd13"
http_archive(
    name = "catch2",
    strip_prefix = "Catch2-{}".format(catch2_tag),
    type = "zip",
    url = "https://github.com/catchorg/Catch2/archive/v{}.zip".format(catch2_tag),
    sha256 = catch2_sha256,
)

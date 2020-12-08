workspace(name = "swiss_dasch_skunkworks")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# get c++ clang+llvm official binaries
# for macOS
http_archive(
    name = "clang_llvm_11.0.0_x86_64_apple_darwin",
    build_file = "@swiss_dasch_skunkworks//toolchain:compiler.BUILD",
    strip_prefix = "clang+llvm-11.0.0-x86_64-apple-darwin",
    url = "https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/clang+llvm-11.0.0-x86_64-apple-darwin.tar.xz",
    sha256 = "b93886ab0025cbbdbb08b46e5e403a462b0ce034811c929e96ed66c2b07fe63a",
)

# for ubuntu 20.04
http_archive(
    name = "clang_llvm_11.0.0_x86_64_linux_gnu_ubuntu_20.04",
    build_file = "@swiss_dasch_skunkworks//toolchain:compiler.BUILD",
    strip_prefix = "clang+llvm-11.0.0-x86_64-linux-gnu-ubuntu-20.04",
    url = "https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/clang+llvm-11.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz",
    sha256 = "829f5fb0ebda1d8716464394f97d5475d465ddc7bea2879c0601316b611ff6db",
)

# The rules_foreign_cc rule repository - commit from 26.10.2020
rules_foreign_cc_version = "d54c78ab86b40770ee19f0949db9d74a831ab9f0"
rules_foreign_cc_version_sha256 = "3c6445404e9e5d17fa0ecdef61be00dd93b20222c11f45e146a98c0a3f67defa"
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-%s" % rules_foreign_cc_version,
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/%s.zip" % rules_foreign_cc_version,
    sha256 = rules_foreign_cc_version_sha256,
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

# Register default toolchain. It is also possible to register
# custom toolchains.
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

# Skunk Works

This repository holds the new DaSCH Service Platform Backend, reimplemented using Clean-Architecture principles,
implementing the CQRS pattern and using Event-Sourcing.

## Style Guide

The code follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and the
exceptions which are documented in this section.

## Linux Container

To test if the build and tests run under Linux, you can start a Linux Docker container:
```bash
$ make start-linux-container
```

Then inside the container, run the test in the following way:
```bash
$ bazel test --config=linux //...
```

## Experimental Apple Silicon Support

To run the tests on a Apple Silicon machine, run the following:
```bash
$ USE_BAZEL_VERSION=last_green bazelisk test -c opt --cpu=darwin_arm64 //...
```

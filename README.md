# Skunk Works

This repository holds the new DaSCH Service Platform Backend, reimplemented using Clean-Architecture principles,
implementing the CQRS pattern and using Event-Sourcing.

## Style Guide

The code follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and the
exceptions which are documented in this section.

## Linux Container

To test if the build and tests run under Linux, you can start a Linux Docker container,
which matches your current CPU platform:
```bash
$ make start-linux-amd64-container
$ make start-linux-arm64-container
$ make start-linux-armv7-container
```

Then inside the container, change into the `src` directory, and run
the `test-linux` make target:
```bash
$ cd src
$ make test-linux
```

## Experimental Apple Silicon Support

To run the tests on a Apple Silicon machine, run the following:
```bash
$ USE_BAZEL_VERSION=last_green bazel test -c opt --cpu=darwin_arm64 //...
```

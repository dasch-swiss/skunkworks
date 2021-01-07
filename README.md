# Skunk Works

This repository holds the new DaSCH Service Platform Backend, reimplemented using Clean-Architecture principles,
implementing the CQRS pattern and using Event-Sourcing.

## Style Guide

The code follows the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and the
exceptions which are documented in this section.

## Prerequisites

- on macOS, this might be necessary:
  ```asm
  export DEVELOPER_DIR=/Applications/Xcode.app/Contents/Developer
  export SDKROOT=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
  ```

### On macOS install the following:

- Homebrew:

  Follow instructions on https://brew.sh 

- Apple Command Line Tools:
  ```bash
  $ xcode-select --install
  ```

- Java 11:
  ```
  $ brew tap AdoptOpenJDK/openjdk
  $ brew cask install AdoptOpenJDK/openjdk/adoptopenjdk11
  ```

  To pin the version of Java, please add this environment variable to your starup script:
  ```
  export JAVA_HOME=`/usr/libexec/java_home -v 11`
  ```

- Node:
  ```
  $ brew install node
  $ brew install n // optional
  $ n lts // optional
  ```

- Bazel:
  ```
  $ npm install -g @bazel/bazelisk
  $ npm install -g @bazel/buildozer
  ```

- CMake:
  ```
  $ brew install cmake
  ```

## References

### DDD, CQRS, Event Sourcing
- The Value of Objects (DDD Europe 2020): https://youtu.be/YaFczCxnXyA

### Clean Code, Clean Architecture
- Breaking Dependencies (CppCon 2020): The SOLID Principles: https://youtu.be/Ntraj80qN2k
- Test Driven C++ (CppCon 2020): https://youtu.be/N2gTxeIHMP0
    - further resources: https://levelofindirection.com/refs/tdcpp.html

### Other
- Performance Matters (CppCon 2020): https://youtu.be/koTf7u0v41o


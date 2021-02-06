# Determine this makefile's path.
# Be sure to place this BEFORE `include` directives, if any.
# THIS_FILE := $(lastword $(MAKEFILE_LIST))
THIS_FILE := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

include vars.mk

.PHONY: docs-build
docs-build: ## build docs into the local 'site' folder
	mkdocs build

.PHONY: docs-serve
docs-serve: ## serve docs for local viewing
	mkdocs serve

.PHONY: docs-publish
docs-publish: ## build and publish docs to Github Pages
	mkdocs gh-deploy

.PHONY: install-python-requirements
install-python-requirements: ## install python requirements for documentation
	pip3 install -r requirements.txt

.PHONY: build
build: ## build the project
	bazel build //...

.PHONY: build-linux
build-linux: ## build the project under Linux
	bazel build --config=linux //...

.PHONY: build-darwin-arm64
build-darwin-arm64: ## build the project on an Apple Silicon machine
	USE_BAZEL_VERSION=last_green bazel build -c opt --cpu=darwin_arm64 //...

.PHONY: test
test: ## test the project
	bazel test //...

.PHONY: test-linux
test-linux: ## test the project under linux
	bazel test --config=linux //...

.PHONY: test-apple-silicon
test-apple-silicon: ## test the project on an Apple Silicon machine
	USE_BAZEL_VERSION=last_green bazel test -c opt --cpu=darwin_arm64 //...

.PHONY: start-linux-intel-container
start-linux-intel-container: ## Start the Linux amd64 Docker container which can be used to run builds inside
	docker run -it --rm --platform linux/amd64 -v ${PWD}:/src daschswiss/sipi-base:2.3 bin/bash

.PHONY: start-linux-arm-container
start-linux-arm-container: ## Start the Linux arm64 Docker container which can be used to run builds inside
	docker run -it --rm --platform linux/arm64 -v ${PWD}:/src daschswiss/sipi-base:2.3 bin/bash

.PHONY: start-linux-rpi-container
start-linux-rpi-container: ## Start the Linux arm/v7 Docker container which can be used to run builds inside
	docker run -it --rm --platform linux/arm/v7 -v ${PWD}:/src daschswiss/sipi-base:2.3 bin/bash

.PHONY: help
help: ## this help
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST) | sort

.DEFAULT_GOAL := help

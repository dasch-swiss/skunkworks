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

.PHONY: build-arm
build-arm: ## build the project
	USE_BAZEL_VERSION=last_green bazel build -c opt --cpu=darwin_arm64 //...

.PHONY: test
test: ## test the project
	bazel test //...

.PHONY: test-arm
test-arm: ## build the project
	USE_BAZEL_VERSION=last_green bazel test -c opt --cpu=darwin_arm64 //...

.PHONY: start-linux-container
start-linux-container: ## Start the Linux Docker container which can be used to run builds inside
	docker run -it --rm -v ${PWD}:/src daschswiss/sipi-base:latest bin/bash

.PHONY: help
help: ## this help
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST) | sort

.DEFAULT_GOAL := help

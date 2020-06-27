# OpenSpiel Project Template

[![Build Status](https://travis-ci.com/dmorrill10/open_spiel-project-template.svg?token=&branch=master)](https://travis-ci.com/dmorrill10/open_spiel-project-template)

A template for projects that wish to use [OpenSpiel](https://github.com/deepmind/open_spiel) as a third party library.

## What and Why?

A critical concept in software development is it the idea of a library. The library exposes interfaces to functionality that another project can utilize. This interface allows the consumer to access library functionality from outside of the library itself, which allows both the library and the consumer to develop independently, as long the library's interface does not change. Clear separation and a limited interface also allow the consumer to more easily upgrade to library changes than if the consumer was embedded into the library itself.

[OpenSpiel](https://github.com/deepmind/open_spiel) is a polyglot library managed by [CMake](https://cmake.org/). CMake is a tool that constructs Makefile build trees for building libraries and executables, but it does not expose a convenient interface to library components---particularly C++ components---by default, like, *e.g.*, `cargo`, `pip`, `yarn`/`npm`, and `gem` do for Rust, Python, JavaScript, and Ruby. There are ways to construct libraries so that CMake does provide an interface like this, but using it is not entirely straightforward.

Perhaps the easiest way to use OpenSpiel is to fork the repository and embed your new code within OpenSpiel itself. That way, you are able to reuse all of its build structure and files, making only small modifications to them to account for your new code. But now what do you do if OpenSpiel changes and you want to incorporate those changes into your fork? Merging these now diverging repositories could become difficult and error prone. And what if you want to make contributions back to OpenSpiel? Picking out just the changes that you want to contribute and ensuring that they do not depend on any of the other code you have added can be tricky and error prone as well. All of these problems arise because we did not impose a clear boundary between the OpenSpiel library and consumer code.

This repository is meant to allow one to easily use the OpenSpiel library in a way does maintain a clear boundary between library and consumer. It is a flexible and simple template based on a single `Makefile`, a single `src/CMakeLists.txt` file, and a handful of bash scripts in `scripts`. There is also a [Singularity](https://sylabs.io/docs/) container definition, `Singularity.def`, for self-contained builds in environments that support containers.

This template was originally designed for interfacing with OpenSpiel's C++ code, and by default all other language interfaces are disabled, but the structure that this template imposes could be useful more generally. I am not actively developing support for other languages but I welcome pull requests that would add optional functionality.


## Usage

The idea is that you copy or fork this repository, then write your code in `src` or subdirectories therein assuming that OpenSpiel headers can be accessed via  `#include "open_spiel/..."`, modifying `src/CMakeLists.txt` as necessary. Then running `make` should download the OpenSpiel code to `src` with its dependencies and build everything together into a `build.*` directory. Depending on the suffix, the build will be built with different flags. `Release` is the default build type and it is aggressively optimized. See `src/CMakeLists` for the flags that are used with different build types.

There is an example subdirectory in `src`, `src/example`, that describes how to add code subdirectories, libraries, executables, and tests.

You can run an example test by running

```
$ make
. . . (lots of output) . . .
[100%] Built target code_test

$ ./build/example/code_test
0 1
0 1 0
0 1 0 1
0 1 1
0 2 0
0 2 1
1 0
1 0 0
1 0 0 1
1 0 1
2 0
2 0 0 1
Success, all Kuhn history strings printed in the expected order.
```


## Dependencies

OpenSpiel and most of its dependencies are downloaded as necessary by `make` rules to directories in `src`. The exceptions are `bash`, `make`, `clang`, `glibc`, `cmake`, `unzip`, `git`, and `wget`. Please install these using your system installer, or use [Singularity](https://sylabs.io/docs/) to avoid installing anything. *E.g.*, on Fedora, run

```
sudo yum update -y
sudo yum install bash make clang glibc cmake unzip git wget -y
```

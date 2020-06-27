#!/usr/bin/env bash
set -e  # exit when any command fails
set -x

# Setting -DCMAKE_EXPORT_COMPILE_COMMANDS ensures that `compile_commands.json`
# will be created. This file can be used with `clangd`-based tools or IDEs
# to statically analyze code.
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=$1 ../src

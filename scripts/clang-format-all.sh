#!/bin/sh
# Format all files with clang
find ./ -name *.cpp -o -name *.h | xargs clang-format-5.0 -i -style=file



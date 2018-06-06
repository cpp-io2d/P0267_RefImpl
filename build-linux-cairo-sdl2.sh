#!/bin/bash -e

cd "$(dirname "$0")"
export CXX=g++-7
# git clone --recurse-submodules https://github.com/mikebmcl/P0267_RefImpl
# cd P0267_RefImpl
mkdir -p Debug || true
cd Debug
cmake -G "Unix Makefiles" --config Debug "-DCMAKE_BUILD_TYPE=Debug" -DIO2D_DEFAULT=CAIRO_SDL2 "$@" ../.
make

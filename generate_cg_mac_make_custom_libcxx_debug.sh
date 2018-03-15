#!/bin/sh
set -x

rm -rf Debug
mkdir Debug
cd Debug

export CXXFLAGS="-nostdinc++ -I ${HOME}/Developer/llvm_clean/build/include/c++/v1"
export LDFLAGS="-L ${HOME}/Developer/llvm_clean/build/lib"

cmake -G "Unix Makefiles" --config Debug -DCMAKE_BUILD_TYPE=Debug -DIO2D_BACKEND=COREGRAPHICS_MAC ../.


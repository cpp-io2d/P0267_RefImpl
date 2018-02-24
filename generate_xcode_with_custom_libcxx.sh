#!/bin/sh
set -x

rm -rf Debug
mkdir Debug
cd Debug

export CXXFLAGS="-nostdinc++ -I ${HOME}/Developer/llvm_clean/build/include/c++/v1"
export LDFLAGS="-L ${HOME}/Developer/llvm_clean/build/lib"

cmake -G "Xcode" ../.


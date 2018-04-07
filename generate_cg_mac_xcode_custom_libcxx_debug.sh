#!/bin/sh
set -x

rm -rf Debug
mkdir Debug
cd Debug

export CXXFLAGS="-nostdinc++ -I ${HOME}/Developer/llvm_clean/build/include/c++/v1"
export LDFLAGS="-L ${HOME}/Developer/llvm_clean/build/lib"

# cmake -G "Xcode" --config Debug -DCMAKE_BUILD_TYPE=Debug -DIO2D_BACKEND=COREGRAPHICS_MAC ../.


#cmake -G "Xcode" --config Debug -DCMAKE_BUILD_TYPE=Debug -DIO2D_DEFAULT=COREGRAPHICS_MAC -DIO2D_ENABLED=COREGRAPHICS_MAC ../.


cmake -G "Xcode" --config Debug -DCMAKE_BUILD_TYPE=Debug -DIO2D_DEFAULT=COREGRAPHICS_MAC ../.

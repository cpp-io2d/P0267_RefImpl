#!/bin/sh
set -x

rm -rf Debug
mkdir Debug
cd Debug

export CXXFLAGS="-nostdinc++ -I${HOME}/Developer/llvm_clean/build/include/c++/v1 -I/opt/X11/include -I/opt/local/include -I/usr/local/include"
export LDFLAGS="-L${HOME}/Developer/llvm_clean/build/lib -L/opt/X11/lib -L/opt/local/lib -L/usr/local/lib"

#cmake -G "Xcode" --config Debug -DCMAKE_BUILD_TYPE=Debug -DIO2D_BACKEND=CAIRO_XLIB ../.

cmake -G "Xcode" --config Debug -DCMAKE_BUILD_TYPE=Debug -DIO2D_DEFAULT=CAIRO_XLIB ../.

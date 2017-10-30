#!/bin/sh
CXXFLAGSVALS="$@"
CXXFLAGSVALS+=" -std=c++1z -Wall -Wno-float-equal -Wno-padded"

echo "Running './configure CC=clang-mp-5.0 CXX=clang++-mp-5.0 CXXFLAGS=\"${CXXFLAGSVALS}\" LDFLAGS=\"-L/opt/local/lib\" CPPFLAGS=\"-isystem/opt/local/include\""

./configure CC=clang-mp-5.0 CXX=clang++-mp-5.0 CXXFLAGS="${CXXFLAGSVALS}"  LDFLAGS="-L/opt/local/lib" CPPFLAGS="-isystem/opt/local/include"


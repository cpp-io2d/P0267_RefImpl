#!/bin/sh
CXXFLAGSVALS="$@"
CXXFLAGSVALS+=" -std=c++1z -Wall -Wno-float-equal -Wno-padded"

echo "Running './configure CC=gcc-mp-8  CXX=g++-mp-8 CXXFLAGS=\"${CXXFLAGSVALS}\" LDFLAGS=\"-L/opt/local/lib\" CPPFLAGS=\"-isystem/opt/local/include\""

./configure CC=gcc-mp-8 CXX=g++-mp-8 CXXFLAGS="${CXXFLAGSVALS}"  LDFLAGS="-L/opt/local/lib -lstdc++fs" CPPFLAGS="-isystem/opt/local/include"


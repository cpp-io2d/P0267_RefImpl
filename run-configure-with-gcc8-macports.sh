#!/bin/sh
CXXFLAGSVALS="$@"
CXXFLAGSVALS+=" -std=c++1z -Wall -Wno-float-equal -Wno-padded"

echo "Running './configure CC=gcc-mp-8 CFLAGS=\"-g\" CXX=g++-mp-8 CXXFLAGS=\"${CXXFLAGSVALS}\" LDFLAGS=\"-L/opt/local/lib\" CPPFLAGS=\"-isystem/opt/local/include\""
#echo "Running './configure CC=gcc-mp-8 CFLAGS=\"-g\" CXX=g++-mp-8 CXXFLAGS=\"-g -std=c++1z -Wall -Wno-float-equal -Wno-padded\" LDFLAGS=\"-L/opt/local/lib\" CPPFLAGS=\"-isystem/opt/local/include\""

./configure CC=gcc-mp-8 CFLAGS="-g" CXX=g++-mp-8 CXXFLAGS="${CXXFLAGSVALS}"  LDFLAGS="-L/opt/local/lib" CPPFLAGS="-isystem/opt/local/include"
#./configure CC=gcc-mp-8 CFLAGS="-g" CXX=g++-mp-8 CXXFLAGS="-g -std=c++1z -Wall -Wno-float-equal -Wno-padded" LDFLAGS="-L/opt/local/lib" CPPFLAGS="-isystem/opt/local/include"

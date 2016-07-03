#!/bin/sh
echo "Running './configure CC=gcc-4.9 CFLAGS=\"-g -fdiagnostics-color\" CXX=g++-4.9 CXXFLAGS=\"-g -std=c++14 -fdiagnostics-color -Wall -pedantic\""
./configure CC=gcc-4.9 CFLAGS="-g -fdiagnostics-color" CXX=g++-4.9 CXXFLAGS="-g -std=c++14 -fdiagnostics-color -Wall -pedantic"

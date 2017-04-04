#!/bin/sh
echo "Running './configure CC=gcc-6 CFLAGS=\"-g -fdiagnostics-color\" CXX=g++-6 CXXFLAGS=\"-g -std=c++17 -fdiagnostics-color -Wall -pedantic\""
./configure CC=gcc-6 CFLAGS="-g -fdiagnostics-color" CXX=g++-6 CXXFLAGS="-g -std=c++17 -fdiagnostics-color -Wall -pedantic"

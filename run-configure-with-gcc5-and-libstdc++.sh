#!/bin/sh
echo "Running './configure CC=gcc-5 CFLAGS=\"-g -fdiagnostics-color\" CXX=g++-5 CXXFLAGS=\"-g -std=c++14 -fdiagnostics-color -Wall -pedantic\""
./configure CC=gcc-5 CFLAGS="-g -fdiagnostics-color" CXX=g++-5 CXXFLAGS="-g -std=c++14 -fdiagnostics-color -Wall -pedantic"

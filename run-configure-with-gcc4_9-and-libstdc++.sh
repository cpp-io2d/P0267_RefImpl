#!/bin/sh
echo "Running './configure CC=gcc-4.9 CFLAGS=\"-g -fdiagnostics-color\" CXX=g++-4.9 CXXFLAGS=\"-g -std=c++1y -fdiagnostics-color\""
./configure CC=gcc-4.9 CFLAGS="-g -fdiagnostics-color" CXX=g++-4.9 CXXFLAGS="-g -std=c++1y -fdiagnostics-color"

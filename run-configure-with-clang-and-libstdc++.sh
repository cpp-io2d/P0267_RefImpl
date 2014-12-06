#!/bin/sh
echo "Running './configure CC=clang CXX=clang++ CXXFLAGS=\"-g -stdlib=libstdc++ -std=c++14\" LDFLAGS=\"-stdlib=libstdc++\""
./configure CC=clang CXX=clang++ CXXFLAGS="-g -stdlib=libstdc++ -std=c++14" LDFLAGS="-stdlib=libstdc++"

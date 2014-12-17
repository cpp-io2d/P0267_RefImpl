#!/bin/sh
echo "Running './configure CC=clang CFLAGS=\"-g\" CXX=clang++ CXXFLAGS=\"-g -stdlib=libstdc++ -std=c++14\" LDFLAGS=\"-stdlib=libstdc++\""
./configure CC=clang CFLAGS="-g" CXX=clang++ CXXFLAGS="-g -stdlib=libstdc++ -std=c++14" LDFLAGS="-stdlib=libstdc++"

#!/bin/bash


echo '''if(EXISTS runtest.cmake)
    include(runtest.cmake)
endif()''' >> CMakeLists.txt

cmake "-DCMAKE_CXX_CPPCHECK=/usr/bin/cppcheck;--std=c++17;--language=c++;--enable=all;--output-file=cppcheck.txt" .

make

make RUNTEST -j4

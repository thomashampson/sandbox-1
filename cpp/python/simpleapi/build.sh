#!/bin/bash
set -x

g++ -o dynamic_functions.so \
  -I/usr/include/python2.7 \
  -fPIC \
  -shared \
  dynamic_functions.cpp \
  -lboost_python

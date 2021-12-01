#!/bin/sh -e
g++ -std=c++0x screenRecord.cpp -lX11 `pkg-config --cflags opencv` `pkg-config --libs opencv` -o main


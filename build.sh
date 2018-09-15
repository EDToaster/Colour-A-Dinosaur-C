#! /usr/bin/env bash

gcc -Wall -g -o main *.c `sdl2-config --cflags --libs`

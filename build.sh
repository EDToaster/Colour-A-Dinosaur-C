#! /usr/bin/env bash

gcc -Wall -g -o main main.c `pkg-config --libs --cflags gtk+-3.0`

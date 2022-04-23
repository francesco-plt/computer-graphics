#!/bin/bash

function cvk {
	g++ -std=c++17 -O2 -lglfw -lvulkan -ldl -lpthread $1 -o  $(basename -s ".cpp" "$1")
}

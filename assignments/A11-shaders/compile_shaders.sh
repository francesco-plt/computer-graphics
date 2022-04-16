#!/bin/bash

echo 'compiling...'
glslc shaders/Shader.vert -o shaders/Vert.spv
glslc shaders/Shader.frag -o shaders/Frag.spv
echo 'done'
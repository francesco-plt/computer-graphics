#!bin/sh

echo 'compiling...'
glslc shaders/SkyboxShader.vert -o shaders/SkyBoxVert.spv
glslc shaders/SkyboxShader.frag -o shaders/SkyBoxFrag.spv
glslc shaders/PBRShader.vert -o shaders/PBRVert.spv
glslc shaders/PBRShader.frag -o shaders/PBRFrag.spv
echo 'done'
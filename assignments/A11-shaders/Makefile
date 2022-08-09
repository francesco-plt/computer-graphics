PWD = $(shell pwd)
PROJ_NAME = $(shell cut -c 1-3 <<< $(notdir $(PWD)))
CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread

$(PROJ_NAME): main.cpp
	g++ $(CFLAGS) $(INC) -o $(PROJ_NAME) main.cpp $(LDFLAGS)

.PHONY: test clean

test: $(PROJ_NAME)
	./$(PROJ_NAME)

build:
	glslc shaders/Shader.frag -o Frag.spv
	glslc shaders/Shader.vert -o Vert.spv
	g++ $(CFLAGS) $(INC) -o $(PROJ_NAME) main.cpp $(LDFLAGS)
	

clean:
	rm -f $(PROJ_NAME)	

shad:
	glslc shaders/Shader.frag -o Frag.spv
	glslc shaders/Shader.vert -o Vert.spv
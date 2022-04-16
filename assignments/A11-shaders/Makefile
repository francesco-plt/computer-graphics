PROJ_NAME = $(notdir $(shell pwd))
CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread

$(PROJ_NAME): main.cpp
	g++ $(CFLAGS) $(INC) -o $(PROJ_NAME) main.cpp $(LDFLAGS)

.PHONY: test clean

test: $(PROJ_NAME)
	./$(PROJ_NAME)

build:
	$(info compiling shaders...)
	@glslc shaders/Shader.vert -o shaders/Vert.spv
	@glslc shaders/Shader.frag -o shaders/Frag.spv
	$(info done. compiling program...)
	@g++ $(CFLAGS) $(INC) -o $(PROJ_NAME) main.cpp $(LDFLAGS)

clean:
	rm -f $(PROJ_NAME)	

PROJ_NAME = $(notdir $(shell pwd))
CFLAGS = -std=c++17 -O2
OPTFLAGS = -j 4 -pipe
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread

$(PROJ_NAME): main.cpp
	g++ $(CFLAGS) $(OPTFLAGS) $(INC) -o $(PROJ_NAME) main.cpp $(LDFLAGS)

.PHONY: test clean

test: $(PROJ_NAME)
	./$(PROJ_NAME)

build:
	g++ $(CFLAGS) $(INC) -o $(PROJ_NAME) main.cpp $(LDFLAGS)

clean:
	rm -f $(PROJ_NAME)	

shdrs:
	VERT = $(shell find shaders -type f -iname '*.vert' | sed 's/.vert//g')
	FRAG = $(shell find shaders -type f -iname '*.frag' | sed 's/.frag//g')

	glslc -o $(VERT) -c $(VERT).vert
	glslc -o $(FRAG) -c $(FRAG).frag
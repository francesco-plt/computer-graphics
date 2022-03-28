PROJ_NAME = $(notdir $(shell pwd))
CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread

$(PROJ_NAME): main.cpp
	g++ $(CFLAGS) $(INC) -o $(PROJ_NAME) main.cpp $(LDFLAGS)

.PHONY: test clean

test: $(PROJ_NAME)
	./$(PROJ_NAME)

clean:
	rm -f $(PROJ_NAME)

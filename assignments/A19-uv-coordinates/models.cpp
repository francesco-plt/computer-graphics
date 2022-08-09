#include "models/vertex.h"
#include "models/cube.cpp"
#include "models/can.cpp"

void makeModels()
{
	createCube();
	createCan(36, 1, 3);
}

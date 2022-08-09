#include "models/cylinder.cpp"
#include "models/cube.cpp"
#include "models/sphere.cpp"
#include "models/spring.cpp"
#include "models/vertex.h"

// std::vector<Vertex> M1_vertices;
// std::vector<Vertex> M2_vertices;
// std::vector<Vertex> M3_vertices;
// std::vector<Vertex> M4_vertices;

void makeModels()
{
	createCube();
	createCylinder(36, 1.0, 2.0);
	createSphere(32, 32, 1);
	createSpring(36, 100, 0.6, 2, 5, 2);
}
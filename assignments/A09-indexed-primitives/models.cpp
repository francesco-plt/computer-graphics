#include "models/cylinder.cpp"
#include "models/cube.cpp"
#include "models/sphere.cpp"
#include "models/spring.cpp"

void makeModels()
{
    createCube();
    createCylinder(36, 1.0, 2.0);
    createSphere(32, 32, 1);
    createSpring(36, 100, 0.4, 4, 3, 0.8);
}
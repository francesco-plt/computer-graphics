#include "models/cylinder.cpp"
#include "models/cube.cpp"
#include "models/sphere.cpp"
#include "models/spring.cpp"

void makeModels()
{
    createCube();
    createCylinder(36, 1.0, 2.0);
    createSphere(32, 32, 1);
    createSpring(36, 36, 0.7f, 0.08f, 0.4f);
}
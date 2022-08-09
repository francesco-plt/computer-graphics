#include "vertex.h"

void createSphere(int hCount, int vCount, float r)
{

    float x, y, z, xy;
    float phi, theta;
    int k1, k2;

    float pi = M_PI;
    float hRectangles = 2 * pi / hCount;
    float vRectangles = pi / vCount;

    int vertCounter = 0;
    int indexCounter = 0;

    M3_vertices.resize(vCount * hCount * 2);

    for (int i = 0; i <= vCount; i++)
    {
        theta = pi / 2 - i * vRectangles;
        xy = r * cos(theta);
        z = r * sin(theta);

        for (int j = 0; j <= hCount; j++)
        {
            phi = j * hRectangles;

            x = xy * cos(phi);
            y = xy * sin(phi);

            M3_vertices[vertCounter].pos = glm::vec3(x, y, z);
            M3_vertices[vertCounter].norm = glm::vec3(x, y, z);
            vertCounter++;
        }
    }

    M3_indices.resize(3 * vCount * hCount * 2);

    for (int i = 0; i < vCount; i++)
    {
        k1 = i * (hCount + 1);
        k2 = k1 + hCount + 1;

        for (int j = 0; j < hCount; j++, k1++, k2++)
        {
            if (i != 0)
            {
                M3_indices[indexCounter] = k1;
                indexCounter++;
                M3_indices[indexCounter] = k2;
                indexCounter++;
                M3_indices[indexCounter] = k1 + 1;
                indexCounter++;
            }

            if (i != vCount - 1)
            {
                M3_indices[indexCounter] = k1 + 1;
                indexCounter++;
                M3_indices[indexCounter] = k2;
                indexCounter++;
                M3_indices[indexCounter] = k2 + 1;
                indexCounter++;
            }
        }
    }
}
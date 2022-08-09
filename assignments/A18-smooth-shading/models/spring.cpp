#include "vertex.h"

void createSpring(int nSlices, float steps, float r, float spireDist, int nRounds, float roundsDist)
{
    //// M4 : Spring
    // Replace the code below, that creates a simple octahedron, with the one to create a spring
    float u = 0;

    float sCx = 0, sCy = 0, sCz = 0;

    M4_vertices.resize(steps * nSlices);

    for (int i = 0; i < steps; i++)
    {
        u = (float)i / steps * nRounds * 2.0 * M_PI;
        sCx = spireDist * cos(u);
        sCy = (roundsDist * u) / M_PI;
        sCz = spireDist * sin(u);
        for (int j = 0; j < nSlices; j++)
        {
            float x = sCx + r * cos((float)j / nSlices * 2.0 * M_PI) * cos(u);
            float y = sCy + r * sin((float)j / nSlices * 2.0 * M_PI);
            float z = sCz + r * cos((float)j / nSlices * 2.0 * M_PI) * sin(u);

            float nx = cos((float)j / nSlices * 2.0 * M_PI) * cos(u);
            float ny = sin((float)j / nSlices * 2.0 * M_PI);
            float nz = cos((float)j / nSlices * 2.0 * M_PI) * sin(u);

            M4_vertices[j + i * nSlices].pos = glm::vec3(x, y, z);
            M4_vertices[j + i * nSlices].norm = glm::vec3(nx, ny, nz);
        }
    }

    M4_indices.resize(3 * (steps * nSlices) * 2);

    int lastVal = 0;

    for (int i = 0; i < steps - 1; i++)
    {
        for (int j = 0; j < nSlices; j++)
        {
            M4_indices[j * 3 + i * nSlices * 3 + 0] = j + i * nSlices;
            M4_indices[j * 3 + i * nSlices * 3 + 1] = j + i * nSlices + nSlices;
            M4_indices[j * 3 + i * nSlices * 3 + 2] = ((j + 1) % nSlices) + nSlices * i;
        }
        lastVal = i * nSlices * 3;
    }

    for (int i = 0; i < steps - 1; i++)
    {
        for (int j = 0; j < nSlices; j++)
        {
            M4_indices[j * 3 + (steps + i) * nSlices * 3 + 0] = j + i * nSlices + nSlices;
            M4_indices[j * 3 + (steps + i) * nSlices * 3 + 1] = ((j + 1) % nSlices) + nSlices * i + nSlices;
            M4_indices[j * 3 + (steps + i) * nSlices * 3 + 2] = ((j + 1) % nSlices) + nSlices * i;
        }
    }
}
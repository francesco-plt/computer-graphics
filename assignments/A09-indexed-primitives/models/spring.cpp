#include <GLFW/glfw3.h>

void createSpring(int nSlices, float steps, float r, float spireDist, int nRounds, float roundsDist)
{
    float u, pi = M_PI;
    float x = 0, y = 0, z = 0;

    M4_vertices.resize(3 * (steps * nSlices));

    for (int i = 0; i < steps; i++)
    {
        float u = (float)i / steps * nRounds * 2.0 * pi;
        // center of i circle
        x = spireDist * cos(u);
        y = (roundsDist * u) / pi;
        z = spireDist * sin(u);
        for (int j = 0; j < nSlices; j++)
        {
            M4_vertices[j * 3 + i * nSlices * 3 + 0] = x + r * cos((float)j / nSlices * 2.0 * pi) * cos(u);
            M4_vertices[j * 3 + i * nSlices * 3 + 1] = y + r * sin((float)j / nSlices * 2.0 * pi);
            M4_vertices[j * 3 + i * nSlices * 3 + 2] = z + r * cos((float)j / nSlices * 2.0 * pi) * sin(u);
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
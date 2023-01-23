#include "vertex.h"

void createCylinder(int nSlices, float radius, float height)
{
    float cx = 0, cy = 0, cz = 0, pi = M_PI;

    int baseIndex = 0;

    M2_vertices.resize(nSlices * 4 + 2);

    // Upper circle
    M2_vertices[baseIndex].pos = glm::vec3(cx, cy + height / 2, cz);
    M2_vertices[baseIndex].norm = glm::vec3(0, 1, 0);

    baseIndex = 1;

    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + radius * cos((float)i / nSlices * 2.0 * pi);
        float y = cy + height / 2;
        float z = cz + radius * sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(0, 1, 0);
    }

    baseIndex = nSlices + 1;

    // Lower circle
    M2_vertices[baseIndex].pos = glm::vec3(cx, cy - height / 2, cz);
    M2_vertices[baseIndex].norm = glm::vec3(0, -1, 0);

    baseIndex = nSlices + 2;

    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + radius * cos((float)i / nSlices * 2.0 * pi);
        float y = cy - height / 2;
        float z = cz + radius * sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(0, -1, 0);
    }

    // sides

    baseIndex = 2 * nSlices + 2;

    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + radius * cos((float)i / nSlices * 2.0 * pi);
        float y = cy + height / 2;
        float z = cz + radius * sin((float)i / nSlices * 2.0 * pi);

        float nx = cos((float)i / nSlices * 2.0 * pi);
        float nz = sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(nx, 0, nz);
    }

    baseIndex = 3 * nSlices + 2;

    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + radius * cos((float)i / nSlices * 2.0 * pi);
        float y = cy - height / 2;
        float z = cz + radius * sin((float)i / nSlices * 2.0 * pi);

        float nx = cos((float)i / nSlices * 2.0 * pi);
        float nz = sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(nx, 0, nz);
    }

    // indices (3 * number of triangles)
    M2_indices.resize(3 * (nSlices * 4));

    for (int i = 0; i < nSlices; i++)
    {
        M2_indices[i * 3 + 0] = 0;
        M2_indices[i * 3 + 1] = i + 1;
        M2_indices[i * 3 + 2] = (i + 1) % nSlices + 1;
    }

    for (int i = nSlices; i < 2 * nSlices; i++)
    {
        M2_indices[i * 3 + 0] = nSlices + 1;
        M2_indices[i * 3 + 1] = i + 2;
        M2_indices[i * 3 + 2] = ((i + 1) % nSlices) + nSlices + 2;
    }

    for (int i = 0; i < nSlices; i++)
    {
        M2_indices[(2 * nSlices + i) * 3 + 0] = 2 * nSlices + 2 + i;
        M2_indices[(2 * nSlices + i) * 3 + 1] = ((i + 1) % nSlices) + 2 * nSlices + 2;
        M2_indices[(2 * nSlices + i) * 3 + 2] = 3 * nSlices + 2 + i;
    }

    for (int i = 0; i < nSlices; i++)
    {
        M2_indices[(3 * nSlices + i) * 3 + 0] = 3 * nSlices + 2 + i;
        M2_indices[(3 * nSlices + i) * 3 + 1] = ((i + 1) % nSlices) + 3 * nSlices + 2;
        M2_indices[(3 * nSlices + i) * 3 + 2] = ((i + 1) % nSlices) + 2 * nSlices + 2;
    }
}
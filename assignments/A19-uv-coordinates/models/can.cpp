#include "vertex.h"

void createCan(int nSlices, float r, float height)
{
    //// M2 : Cylinder

    float cx = 0, cy = 0, cz = 0, pi = M_PI;

    int baseIndex = 0;

    M2_vertices.resize(nSlices * 4 + 4);

    // Upper circle
    M2_vertices[baseIndex].pos = glm::vec3(cx, cy + height / 2, cz);
    M2_vertices[baseIndex].norm = glm::vec3(0, 1, 0);
    M2_vertices[baseIndex].UV = glm::vec2(0.625, 0.125);

    baseIndex = 1;

    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + r * cos((float)i / nSlices * 2.0 * pi);
        float y = cy + height / 2;
        float z = cz + r * sin((float)i / nSlices * 2.0 * pi);

        float u = 0.625 + 0.125 * cos((float)i / nSlices * 2.0 * pi);
        float v = 0.125 + 0.125 * sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(0, 1, 0);
        M2_vertices[baseIndex + i].UV = glm::vec2(u, v);
    }

    baseIndex = nSlices + 1;

    // Lower circle
    M2_vertices[baseIndex].pos = glm::vec3(cx, cy - height / 2, cz);
    M2_vertices[baseIndex].norm = glm::vec3(0, -1, 0);
    M2_vertices[baseIndex].UV = glm::vec2(0.875, 0.125);

    baseIndex = nSlices + 2;

    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + r * cos((float)i / nSlices * 2.0 * pi);
        float y = cy - height / 2;
        float z = cz + r * sin((float)i / nSlices * 2.0 * pi);

        float u = 0.875 + 0.125 * cos((float)i / nSlices * 2.0 * pi);
        float v = 0.125 + 0.125 * sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(0, -1, 0);
        M2_vertices[baseIndex + i].UV = glm::vec2(u, v);
    }

    baseIndex = 2 * nSlices + 2;

    float step = 0.5 / nSlices;
    float u = 1;
    float v = 0.25;
    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + r * cos((float)i / nSlices * 2.0 * pi);
        float y = cy + height / 2;
        float z = cz + r * sin((float)i / nSlices * 2.0 * pi);

        if (i != 0)
        {
            u = u - step;
        }

        float nx = cos((float)i / nSlices * 2.0 * pi);
        float nz = sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(nx, 0, nz);
        M2_vertices[baseIndex + i].UV = glm::vec2(u, v);
    }

    baseIndex = 3 * nSlices + 2;

    // same vertex in pos equal to the first but with different uv coordinate

    M2_vertices[baseIndex].pos = glm::vec3(cx + r, cy + height / 2, cz);
    M2_vertices[baseIndex].norm = glm::vec3(1, 0, 0);
    M2_vertices[baseIndex].UV = glm::vec2(0.5, v);

    baseIndex = 3 * nSlices + 3;

    u = 1;
    v = 0.5;
    for (int i = 0; i < nSlices; i++)
    {
        float x = cx + r * cos((float)i / nSlices * 2.0 * pi);
        float y = cy - height / 2;
        float z = cz + r * sin((float)i / nSlices * 2.0 * pi);

        if (i != 0)
        {
            u = u - step;
        }

        float nx = cos((float)i / nSlices * 2.0 * pi);
        float nz = sin((float)i / nSlices * 2.0 * pi);

        M2_vertices[baseIndex + i].pos = glm::vec3(x, y, z);
        M2_vertices[baseIndex + i].norm = glm::vec3(nx, 0, nz);
        M2_vertices[baseIndex + i].UV = glm::vec2(u, v);
    }

    baseIndex = 4 * nSlices + 3;

    // same vertex in pos equal to the first but with different uv coordinate

    M2_vertices[baseIndex].pos = glm::vec3(cx + r, cy - height / 2, cz);
    M2_vertices[baseIndex].norm = glm::vec3(1, 0, 0);
    M2_vertices[baseIndex].UV = glm::vec2(0.5, v);

    // Resizes the indices array. Repalce the values with the correct number of
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

    for (int i = 0; i < nSlices - 1; i++)
    {
        M2_indices[(2 * nSlices + i) * 3 + 0] = 2 * nSlices + 2 + i;
        M2_indices[(2 * nSlices + i) * 3 + 1] = i + 1 + 2 * nSlices + 2;
        M2_indices[(2 * nSlices + i) * 3 + 2] = 3 * nSlices + 3 + i;
    }

    M2_indices[(2 * nSlices + nSlices - 1) * 3 + 0] = 2 * nSlices + 2 + nSlices - 1;
    M2_indices[(2 * nSlices + nSlices - 1) * 3 + 1] = nSlices + 2 * nSlices + 2;
    M2_indices[(2 * nSlices + nSlices - 1) * 3 + 2] = 4 * nSlices + 2;

    for (int i = 0; i < nSlices - 1; i++)
    {
        M2_indices[(3 * nSlices + i) * 3 + 0] = 3 * nSlices + 3 + i;
        M2_indices[(3 * nSlices + i) * 3 + 1] = i + 1 + 3 * nSlices + 3;
        M2_indices[(3 * nSlices + i) * 3 + 2] = i + 1 + 2 * nSlices + 2;
    }

    M2_indices[(3 * nSlices + nSlices - 1) * 3 + 0] = 3 * nSlices + 3 + nSlices - 1;
    M2_indices[(3 * nSlices + nSlices - 1) * 3 + 1] = nSlices + 3 * nSlices + 3;
    M2_indices[(3 * nSlices + nSlices - 1) * 3 + 2] = 3 * nSlices + 2;
}
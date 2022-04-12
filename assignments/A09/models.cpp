#include <iostream>
#include <vector>

// global structure used to ease vertices handling
struct Vertex
{
    float x;
    float y;
    float z;
};

// this function creates the geometries to be shown, and output thems
// in global variables M1_vertices and M1_indices to M4_vertices and M4_indices
void makeModels()
{
    //// M1 : Cube

    // Resizes the vertices array. Repalce the values with the correct number of
    // vertices components (3 * number of vertices)
    // each vertex is a triplet containing x, y and z coordinates of points in space
    // which make up the vertices of polygon models
    std::vector<Vertex> cubeVertices = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 1},
        {0, 1, 0},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 1},
        {1, 1, 0},
    };

    M1_vertices.resize(8 * 3);
    for (int i = 0; i < 8; i++)
    {
        M1_vertices[3 * i] = cubeVertices[i].x;
        M1_vertices[3 * i + 1] = cubeVertices[i].y;
        M1_vertices[3 * i + 2] = cubeVertices[i].z;
    }

    // Resizes the indices array. Repalce the values with the correct number of
    // indices (3 * number of triangles)
    M1_indices.resize(36);
    M1_indices = {0, 1, 2, 2, 3, 0, // Index Array:
                  0, 3, 4, 4, 3, 7, // 36 indices
                  5, 6, 7, 7, 4, 5, // to the vertices of
                  1, 6, 5, 1, 2, 6, // 12 triangles composing
                  7, 6, 2, 3, 2, 7, // 6 faces of a cube
                  4, 5, 0, 1, 0, 5};

    //// M2 : Cylinder
    // Resizes the vertices array. Replace the values with the correct number of
    // vertices components (3 * number of vertices)

    int nSlices = 36;
    float radius = 1;
    float height = 1;
    // coordinates of the center of the circle
    // which compose the bottom face of the cylinder
    float cx = 0, cy = 0, cz = -3;

    // defining bottom face
    M2_vertices.resize((nSlices + 1) * 6);

    // Vertices definitions
    M2_vertices[0] = cx;
    M2_vertices[1] = cy + height;
    M2_vertices[2] = cz;
    for (int i = 0; i < nSlices; i++)
    {
        M2_vertices[(i + 1) * 3 + 0] = cx + radius * cos((float)(i * 2.0 * M_PI / nSlices)); // x of the vertex
        M2_vertices[(i + 1) * 3 + 1] = cy + height;                                          // y of the vertex
        M2_vertices[(i + 1) * 3 + 2] = cz + radius * sin((float)(i * 2.0 * M_PI / nSlices)); // z of the vertex
    }

    M2_vertices[nSlices * 3 + 3] = cx;
    M2_vertices[nSlices * 3 + 4] = cy;
    M2_vertices[nSlices * 3 + 5] = cz;

    for (int i = 0; i < nSlices; i++)
    {
        M2_vertices[(i + nSlices + 2) * 3 + 0] = cx + radius * cos((float)(i * 2.0 * M_PI / nSlices)); // x of the vertex
        M2_vertices[(i + nSlices + 2) * 3 + 1] = cy;                                                   // y of the vertex
        M2_vertices[(i + nSlices + 2) * 3 + 2] = cz + radius * sin((float)(i * 2.0 * M_PI / nSlices)); // z of the vertex
    }

    // Resizes the indices array. Repalce the values with the correct number of
    // indices (3 * number of triangles)
    M2_indices.resize(20 * nSlices);

    // indices definitions
    for (int i = 0; i < nSlices; i++)
    {
        M2_indices[i * 3] = 0;
        M2_indices[i * 3 + 1] = i + 1;
        M2_indices[i * 3 + 2] = (i + 1) % nSlices + 1;
    }

    for (int i = 0; i < nSlices; i++)
    {
        M2_indices[(i + nSlices) * 3] = nSlices + 1;
        M2_indices[(i + nSlices) * 3 + 1] = nSlices + i + 2;
        M2_indices[(i + nSlices) * 3 + 2] = nSlices + (i + 1) % nSlices + 2;
    }

    // cylinder
    for (int i = 0; i < nSlices * 2; i++)
    {
        M2_indices[2 * 3 * (nSlices + i) + 0] = i + 1;
        M2_indices[2 * 3 * (nSlices + i) + 1] = (i + 1) % nSlices + 1;
        M2_indices[2 * 3 * (nSlices + i) + 2] = nSlices + (i + 1) % nSlices + 1;
        M2_indices[2 * 3 * (nSlices + i) + 3] = nSlices + (i + 1) % nSlices + 1;
        M2_indices[2 * 3 * (nSlices + i) + 4] = nSlices + (i + 1) % nSlices + 2;
        M2_indices[2 * 3 * (nSlices + i) + 5] = (i + 1) % nSlices + 1;
    }

    //// M3 : Sphere
    // Replace the code below, that creates a simple triangle, with the one to create a sphere.

    // Resizes the vertices array. Repalce the values with the correct number of
    // vertices components (3 * number of vertices)
    M3_vertices.resize(9);

    // Vertices definitions
    M3_vertices[0] = 0.0;
    M3_vertices[1] = 1.0;
    M3_vertices[2] = -1.2;
    M3_vertices[3] = -0.866;
    M3_vertices[4] = -0.5;
    M3_vertices[5] = -1.2;
    M3_vertices[6] = 0.866;
    M3_vertices[7] = -0.5;
    M3_vertices[8] = -1.2;

    // Resizes the indices array. Repalce the values with the correct number of
    // indices (3 * number of triangles)
    M3_indices.resize(3);

    // indices definitions
    M3_indices[0] = 0;
    M3_indices[1] = 1;
    M3_indices[2] = 2;

    //// M4 : Spring
    // Replace the code below, that creates a simple octahedron, with the one to create a spring.
    M4_vertices.resize(3 * 6);

    // Vertices definitions
    M4_vertices[0] = 0.0;
    M4_vertices[1] = 1.414;
    M4_vertices[2] = -1.0;
    M4_vertices[3] = 0.0;
    M4_vertices[4] = -1.414;
    M4_vertices[5] = -1.0;
    M4_vertices[6] = -1.0;
    M4_vertices[7] = 0.0;
    M4_vertices[8] = -2.0;
    M4_vertices[9] = -1.0;
    M4_vertices[10] = 0.0;
    M4_vertices[11] = 0.0;
    M4_vertices[12] = 1.0;
    M4_vertices[13] = 0.0;
    M4_vertices[14] = 0.0;
    M4_vertices[15] = 1.0;
    M4_vertices[16] = 0.0;
    M4_vertices[17] = -2.0;

    // Resizes the indices array. Repalce the values with the correct number of
    // indices (3 * number of triangles)
    M4_indices.resize(3 * 8);

    // indices definitions
    M4_indices[0] = 0;
    M4_indices[1] = 2;
    M4_indices[2] = 3;
    M4_indices[3] = 1;
    M4_indices[4] = 3;
    M4_indices[5] = 2;
    M4_indices[6] = 0;
    M4_indices[7] = 3;
    M4_indices[8] = 4;
    M4_indices[9] = 1;
    M4_indices[10] = 4;
    M4_indices[11] = 3;
    M4_indices[12] = 0;
    M4_indices[13] = 4;
    M4_indices[14] = 5;
    M4_indices[15] = 1;
    M4_indices[16] = 5;
    M4_indices[17] = 4;
    M4_indices[18] = 0;
    M4_indices[19] = 5;
    M4_indices[20] = 2;
    M4_indices[21] = 1;
    M4_indices[22] = 2;
    M4_indices[23] = 5;
}
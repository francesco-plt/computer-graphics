void createCube()
{

    struct Vertex
    {
        float x;
        float y;
        float z;
    };

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

    M1_indices.resize(36);
    M1_indices = {0, 1, 2, 2, 3, 0, // Index Array:
                  0, 3, 4, 4, 3, 7, // 36 indices
                  5, 6, 7, 7, 4, 5, // to the vertices of
                  1, 6, 5, 1, 2, 6, // 12 triangles composing
                  7, 6, 2, 3, 2, 7, // 6 faces of a cube
                  4, 5, 0, 1, 0, 5};
}
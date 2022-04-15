/*
    M2: cylinder
    note that:
    NSlices is the resolution of the circumference
    radius is the radius of the cylinder
    height is the height of the cylinder
*/
void createCylinder(int nSlices, float radius, float height)
{
    float cx = 0, cy = 0, cz = -3;

    M2_vertices.resize((nSlices + 1) * 6);

    // top face
    M2_vertices[0] = cx;
    M2_vertices[1] = cy + height;
    M2_vertices[2] = cz;
    for (int i = 0; i < nSlices; i++)
    {
        M2_vertices[(i + 1) * 3 + 0] = cx + radius * cos((float)(i * 2.0 * M_PI / nSlices)); // x of the vertex
        M2_vertices[(i + 1) * 3 + 1] = cy + height;                                          // y of the vertex
        M2_vertices[(i + 1) * 3 + 2] = cz + radius * sin((float)(i * 2.0 * M_PI / nSlices)); // z of the vertex
    }

    // bottom face
    M2_vertices[nSlices * 3 + 3] = cx;
    M2_vertices[nSlices * 3 + 4] = cy;
    M2_vertices[nSlices * 3 + 5] = cz;
    for (int i = 0; i < nSlices; i++)
    {
        M2_vertices[(i + nSlices + 2) * 3 + 0] = cx + radius * cos((float)(i * 2.0 * M_PI / nSlices)); // x of the vertex
        M2_vertices[(i + nSlices + 2) * 3 + 1] = cy;                                                   // y of the vertex
        M2_vertices[(i + nSlices + 2) * 3 + 2] = cz + radius * sin((float)(i * 2.0 * M_PI / nSlices)); // z of the vertex
    }

    M2_indices.resize(18 * nSlices);

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

    for (int i = 0; i < nSlices * 2; i++)
    {
        M2_indices[2 * 3 * (nSlices + i) + 0] = i + 1;
        M2_indices[2 * 3 * (nSlices + i) + 1] = (i + 1) % nSlices + 1;
        M2_indices[2 * 3 * (nSlices + i) + 2] = nSlices + (i + 1) % nSlices + 1;
        M2_indices[2 * 3 * (nSlices + i) + 3] = nSlices + (i + 1) % nSlices + 1;
        M2_indices[2 * 3 * (nSlices + i) + 4] = nSlices + (i + 1) % nSlices + 2;
        M2_indices[2 * 3 * (nSlices + i) + 5] = (i + 1) % nSlices + 1;
    }
}
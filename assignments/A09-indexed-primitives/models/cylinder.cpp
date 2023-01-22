void createCylinder(int nSlices, float radius, float height)
{
    // resolution of the cylinder
    float res = 2.0 * M_PI / nSlices;

    // center of the bottom face
    float cx = 0, cy = 0, cz = 0;

    M2_vertices.push_back(cx);
    M2_vertices.push_back(cy);
    M2_vertices.push_back(cz);

    // bottom face
    for (int i = 0; i < nSlices; i++)
    {
        M2_vertices.push_back(cx + radius * cos(i * res));
        M2_vertices.push_back(cy);
        M2_vertices.push_back(cz + radius * sin(i * res));
    }

    // top face
    M2_vertices.push_back(cx);
    M2_vertices.push_back(cy + height);
    M2_vertices.push_back(cz);
    for (int i = 0; i < nSlices; i++)
    {
        M2_vertices.push_back(cx + radius * cos(i * res));
        M2_vertices.push_back(cy + height);
        M2_vertices.push_back(cz + radius * sin(i * res));
    }

    // bottom indices
    for (int i = 0; i < nSlices - 1; i++)
    {
        M2_indices.push_back(0);
        M2_indices.push_back(i + 1);
        M2_indices.push_back(i + 2);
    }
    M2_indices.push_back(0);
    M2_indices.push_back(nSlices);
    M2_indices.push_back(1);

    // top indices
    for (int i = 0; i < nSlices - 1; i++)
    {
        M2_indices.push_back(nSlices + 1);
        M2_indices.push_back(nSlices + 1 + i + 1);
        M2_indices.push_back(nSlices + 1 + i + 2);
    }
    M2_indices.push_back(nSlices + 1);
    M2_indices.push_back(2 * nSlices + 1);
    M2_indices.push_back(nSlices + 2);

    // cylinder indices
    for (int i = 0; i < nSlices - 1; i++)
    {
        M2_indices.push_back(i + 1);
        M2_indices.push_back(nSlices + i + 2);
        M2_indices.push_back(i + 2);

        M2_indices.push_back(nSlices + i + 2);
        M2_indices.push_back(nSlices + i + 3);
        M2_indices.push_back(i + 2);
    }

    // connecting manually the last two triangles
    // which connects the last vertices witg the first ones

    M2_indices.push_back(nSlices);
    M2_indices.push_back(nSlices * 2 + 1);
    M2_indices.push_back(1);

    M2_indices.push_back(nSlices * 2 + 1);
    M2_indices.push_back(nSlices + 2);
    M2_indices.push_back(1);
}
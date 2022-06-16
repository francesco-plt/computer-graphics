void createCylinder(int nSlices, float radius, float height)
{
    // resolution of the cylinder
    float res = 2.0 * M_PI / nSlices;

    /* ---------- VERTICES ---------- */

    // center of the bottom face circumcircle
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

    M2_vertices.push_back(cx);
    M2_vertices.push_back(cy + height);
    M2_vertices.push_back(cz);

    // top face
    for (int i = 0; i < nSlices; i++)
    {
        M2_vertices.push_back(cx + radius * cos(i * res));
        M2_vertices.push_back(cy + height);
        M2_vertices.push_back(cz + radius * sin(i * res));
    }

    /* ---------- INDICES ---------- */

    int k1 = 0;           // 1st vertex index at base
    int k2 = nSlices + 1; // 1st vertex index at top

    // M2_indices for the side surface
    for (int i = 0; i < nSlices; ++i, ++k1, ++k2)
    {
        // 2 triangles per sector
        // k1 => k1+1 => k2
        M2_indices.push_back(k1);
        M2_indices.push_back(k1 + 1);
        M2_indices.push_back(k2);

        // k2 => k1+1 => k2+1
        M2_indices.push_back(k2);
        M2_indices.push_back(k1 + 1);
        M2_indices.push_back(k2 + 1);
    }

    int baseCenterIndex = 0;
    int topCenterIndex = nSlices + 1;

    // M2_indices for bottom surfaces
    for (int i = 0, k = baseCenterIndex + 1; i < nSlices; ++i, ++k)
    {
        if (i < nSlices - 1)
        {
            M2_indices.push_back(baseCenterIndex);
            M2_indices.push_back(k + 1);
            M2_indices.push_back(k);
        }
        else // last triangle
        {
            M2_indices.push_back(baseCenterIndex);
            M2_indices.push_back(baseCenterIndex + 1);
            M2_indices.push_back(k);
        }
    }

    // M2_indices for the top surface
    for (int i = 0, k = topCenterIndex + 1; i < nSlices; ++i, ++k)
    {
        if (i < nSlices - 1)
        {
            M2_indices.push_back(topCenterIndex);
            M2_indices.push_back(k);
            M2_indices.push_back(k + 1);
        }
        else // last triangle
        {
            M2_indices.push_back(topCenterIndex);
            M2_indices.push_back(k);
            M2_indices.push_back(topCenterIndex + 1);
        }
    }
}
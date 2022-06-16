void createSphere(int hCount, int vCount, float r)
{
    float pi = M_PI;
    float hRectangles, vRectangles;
    float x, y, z, phi, theta;
    int k1, k2;

    // the range of horizontal rectangles angles is from 0 to 360 degrees (360 total)
    // the vertical rectangles angles range from 90 (top) to -90 degrees (bottom) (180 total)
    hRectangles = 2 * pi / hCount;
    vRectangles = pi / vCount;

    for (int i = 0; i <= vCount; i++)
    {
        theta = i * vRectangles;
        for (int j = 0; j <= hCount; j++)
        {
            phi = j * hRectangles;
            x = r * cosf(phi) * sinf(theta);
            y = r * cosf(theta);
            z = r * sinf(phi) * sinf(theta);
            M3_vertices.push_back(x);
            M3_vertices.push_back(y);
            M3_vertices.push_back(z);
        }
    }

    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    // 2 triangles per horizontal step (hStep), excluding first and last stacks
    // k1 => k2 => k1+1
    // M3_indices.resize(hCount * vCount * 3 + 3);
    for (int i = 0; i < vCount; i++)
    {
        k1 = i * (hCount + 1); // beginning of current horizontal step (hStep)
        k2 = k1 + hCount + 1;  // beginning of next horizontal step (hStep)

        for (int j = 0; j < hCount; j++, k1++, k2++)
        {
            // 2 triangles per horizontal step,

            // excluding first stack
            // k1 => k2 => k1+1
            if (i != 0)
            {
                M3_indices.push_back(k1);
                M3_indices.push_back(k2);
                M3_indices.push_back(k1 + 1);
            }

            // and last stack
            // k1+1 => k2 => k2+1
            if (i != (vCount - 1))
            {
                M3_indices.push_back(k1 + 1);
                M3_indices.push_back(k2);
                M3_indices.push_back(k2 + 1);
            }
        }
    }
}
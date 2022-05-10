void createSphere(int hCount, int vCount, float r)
{
    float vStep, hStep, phi, theta, x, y, z, pi = M_PI;
    int k1, k2;

    /*
        A sphere is a circle rotated around a diameter generated
        by a sphere. Those are the parametric equations for
        a surface revolution:
        f(u) * cos(v)
        f(u) * sin(v)
        g(u)
        Where f(u), g(u) are the parametric equations of the rotate curve.
        For a circle those are:
        f(u) = r * cos(u)
        g(u) = r * sin(u)
        Putting all together:
        r * cos(u) * cos(v) = r * cos(phi) * cos(theta)
        r * cos(u) * sin(v) = r * cos(phi) * sin(theta)
        r * sin(u)          = r * sin(phi)
    */

    // M3_vertices.resize(hCount * vCount * 3 + 3); is not needed
    // when using push_back, which automatically resizes the vector

    hStep = 2 * pi / hCount;
    vStep = pi / vCount;
    for (int i = 0; i <= vCount; i++)
    {
        phi = pi / 2 - i * vStep;
        for (int j = 0; j <= hCount; j++)
        {
            theta = j * hStep;
            x = r * cosf(phi) * cosf(theta);
            y = r * cosf(phi) * sinf(theta);
            z = r * sinf(phi);
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
        k1 = i * (hCount + 1); // beginning of current vertical step (vStep)
        k2 = k1 + hCount + 1;  // beginning of next vertical step (vStep)

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
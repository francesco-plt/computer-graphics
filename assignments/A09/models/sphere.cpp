void createSphere(int hCount, int vCount, float r)
{
    float vStep, hStep, phi, theta, x, y, z, pi = M_PI;
    int k1, k2;

    vStep = pi / vCount;
    hStep = 2 * pi / hCount;

    M3_vertices.resize(hCount * vCount);
    for (int i = 0; i <= vCount; i++)
    {
        phi = pi / 2 - i * vStep;
        for (int j = 0; j <= hCount; j++)
        {
            theta = j * vStep;
            x = r * cos(phi) * cos(theta);
            y = r * cos(phi) * sin(theta);
            z = r * sin(phi);
            M3_vertices.push_back(x);
            M3_vertices.push_back(y);
            M3_vertices.push_back(z);
        }
    }

    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1
    M3_indices.resize(hCount * vCount);
    for (int i = 0; i < vCount; i++)
    {
        for (int j = 0; j < hCount; j++)
        {
            k1 = i * hCount + j;
            k2 = k1 + hCount;
            M3_indices.push_back(k1);
            M3_indices.push_back(k2);
            M3_indices.push_back(k1 + 1);
            M3_indices.push_back(k2);
            M3_indices.push_back(k2 + 1);
            M3_indices.push_back(k1 + 1);
        }
    }
}

// possible working variant of indexing:
// for (int i = 0; i < hCount; i++)
//     {
//         for (int j = 0; j < vCount; j++)
//         {
//             k1 = i * (hCount + 1) + j;
//             k2 = k1 + hCount + 1;
//             for (int j = 0; j < hCount; j++)
//             {
//                 if (i != 0)
//                 {
//                     M3_indices.push_back(k1);
//                     M3_indices.push_back(k2);
//                     M3_indices.push_back(k1 + 1);
//                 }

//                 // k1+1 => k2 => k2+1
//                 if (i != (vCount - 1))
//                 {
//                     M3_indices.push_back(k1 + 1);
//                     M3_indices.push_back(k2);
//                     M3_indices.push_back(k2 + 1);
//                 }

//                 k1++;
//                 k2++;
//             }
//         }
//     }
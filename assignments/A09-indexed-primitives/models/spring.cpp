void createSpring(float rounds, float height, float thickness, float radius, int slices, int step)
{
    for (int i = -slices; i <= rounds * 360 + step; i += step)
    {
        for (int j = 0; j < slices; j++)
        {
            float t = (float)i / 360 + (float)j / slices * step / 360;
            t = std::max(0.0f, std::min(rounds, t));
            float a1 = t * M_PI * 2;
            float a2 = (float)j / slices * M_PI * 2;
            float d = radius + thickness * cos(a2);
            M4_vertices.push_back(d * cos(a1));
            M4_vertices.push_back(d * sin(a1));
            M4_vertices.push_back(thickness * sin(a2) + height * t / rounds);
        }
    }
    for (GLuint i = 0; i < (GLuint)M4_vertices.size() / 3 - slices; ++i)
    {
        M4_indices.push_back(i);
        M4_indices.push_back(i + slices);
    }
}
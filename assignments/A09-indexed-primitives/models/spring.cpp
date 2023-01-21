#include <GLFW/glfw3.h>

/*
    The outer loop iterates over the number of steps,
    and the inner loop iterates over the number of slices.
    For each step and slice, the function calculates the
    x, y, and z coordinates of the vertex using a combination
    of trigonometric functions, such as cos and sin.

    The center of each circle is located at a distance of spireDist
    from the origin in the x-z plane. The x and z coordinates of the
    center are calculated using:
    x = spireDist * cos(u);
    z = spireDist * sin(u);
    Where u is the current step divided by the total number of steps,
    multiplied by the number of rounds and two times pi.

    Next, in the inner loop, the cos and sin are used to calculate the x, y,
    and z coordinates of the vertices that make up the spring.
    The x and z coordinates are calculated using:
    M4_vertices[j * 3 + i * nSlices * 3 + 0] = x + r * cos((float)j / nSlices * 2.0 * pi) * cos(u);
    M4_vertices[j * 3 + i * nSlices * 3 + 2] = z + r * cos((float)j / nSlices * 2.0 * pi) * sin(u);
    Where j is the current slice and nSlices is the total number of slices.

    The y coordinate is calculated using:
    M4_vertices[j * 3 + i * nSlices * 3 + 1] = y + r * sin((float)j / nSlices * 2.0 * pi);
    The cos and sin functions are used to calculate the x, y, and z coordinates of each
    vertex in spherical coordinates, where u is the angle around the y-axis and
    j / nSlices * 2.0 * pi is the angle from the x-y plane.
*/

void createSpring(int nSlices, float steps, float r, float spireDist, int nRounds, float roundsDist)
{
    float u, pi = M_PI;
    float x = 0, y = 0, z = 0;

    M4_vertices.resize(3 * (steps * nSlices));

    for (int i = 0; i < steps; i++)
    {
        float u = (float)i / steps * nRounds * 2.0 * pi;
        // center of i circle
        x = spireDist * cos(u);
        y = (roundsDist * u) / pi;
        z = spireDist * sin(u);
        for (int j = 0; j < nSlices; j++)
        {
            M4_vertices[j * 3 + i * nSlices * 3 + 0] = x + r * cos((float)j / nSlices * 2.0 * pi) * cos(u);
            M4_vertices[j * 3 + i * nSlices * 3 + 1] = y + r * sin((float)j / nSlices * 2.0 * pi);
            M4_vertices[j * 3 + i * nSlices * 3 + 2] = z + r * cos((float)j / nSlices * 2.0 * pi) * sin(u);
        }
    }

    M4_indices.resize(3 * (steps * nSlices) * 2);

    int lastVal = 0;

    for (int i = 0; i < steps - 1; i++)
    {
        for (int j = 0; j < nSlices; j++)
        {
            M4_indices[j * 3 + i * nSlices * 3 + 0] = j + i * nSlices;
            M4_indices[j * 3 + i * nSlices * 3 + 1] = j + i * nSlices + nSlices;
            M4_indices[j * 3 + i * nSlices * 3 + 2] = ((j + 1) % nSlices) + nSlices * i;
        }
        lastVal = i * nSlices * 3;
    }

    for (int i = 0; i < steps - 1; i++)
    {
        for (int j = 0; j < nSlices; j++)
        {
            M4_indices[j * 3 + (steps + i) * nSlices * 3 + 0] = j + i * nSlices + nSlices;
            M4_indices[j * 3 + (steps + i) * nSlices * 3 + 1] = ((j + 1) % nSlices) + nSlices * i + nSlices;
            M4_indices[j * 3 + (steps + i) * nSlices * 3 + 2] = ((j + 1) % nSlices) + nSlices * i;
        }
    }
}
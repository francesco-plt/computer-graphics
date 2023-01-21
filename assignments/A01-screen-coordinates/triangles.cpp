/* unit = 0.1
   Sx = 20
   Sy = 20
   plane coordinates:
   (-1, -1) (1, -1)
   (-1, 1)  (1, 1)
*/

// lambda function useful to slim down code
auto Rectangle = [&](float x, float y, float width, float height, int r, int g, int b)
{
    float xa = x;
    float xb = x + width;
    float xc = x;
    float xd = x + width;
    float ya = y;
    float yb = y;
    float yc = y - height;
    float yd = y - height;
    Triangle(xa, ya, xb, yb, xc, yc, r, g, b);
    Triangle(xc, yc, xb, yb, xd, yd, r, g, b);
};

Rectangle(0.1, 0.8, 0.5, 0.6, 0, 0, 1);                             // house body
Triangle(0.1, 0.2, 0.6, 0.2, 0.6 - (0.6 - 0.1) / 2, -0.4, 1, 0, 0); // house roof

Rectangle(0.2, 0.4, 0.1, 0.1, 1, 1, 0); // house window #1
Rectangle(0.4, 0.4, 0.1, 0.1, 1, 1, 0); // house window #1

Rectangle(0.3, 0.8, 0.1, 0.2, 1, 1, 0); // house door

// sun
for (int i = 0; i < 32; i++)
{
    Triangle(0.67 + 0.05 * cos(6.28 / 32 * (i - 0.5)), -0.65 + 0.05 * sin(6.28 / 32 * (i - 0.5)),
             0.67 + 0.10 * cos(6.28 / 32 * i), -0.65 + 0.10 * sin(6.28 / 32 * i),
             0.67 + 0.05 * cos(6.28 / 32 * (i + 0.5)), -0.65 + 0.05 * sin(6.28 / 32 * (i + 0.5)),
             1, 1, 0);
}

// grass
Rectangle(-1, 1, 2, 0.2, 0, 1, 0);

Triangle(-0.04, 0.17, 0.36, -0.45, 0.72, 0.17, 1, 0, 0);
Triangle(0.08, 0.17, 0.08, 0.8, 0.64, 0.17, 0, 0, 1);
Triangle(0.08, 0.8, 0.64, 0.17, 0.64, 0.8, 0, 0, 1);
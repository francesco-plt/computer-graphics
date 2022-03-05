/* unit = 0.1
   Sx = 20
   Sy = 20
   plane coordinates:
   (-1, -1)     (1, -1)

   (-1, 1)      (1, 1)
*/
auto Rectangle = [&](float x, float y, float width, float height, int r, int g, int b) {
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
Rectangle(0.1, 0.8,  0.5, 0.6,  0, 0, 1);  // house body
Triangle(0.1, 0.2,  0.6, 0.2,  0.6-(0.6-0.1)/2, -0.4,  1, 0, 0);  // house roof

Rectangle(0.2, 0.4,  0.1, 0.1,  1, 1, 0);  // house window #1
Rectangle(0.4, 0.4,  0.1, 0.1,  1, 1, 0);  // house window #1

Rectangle(0.3, 0.8,  0.1, 0.2,  1, 1, 0);  // house door
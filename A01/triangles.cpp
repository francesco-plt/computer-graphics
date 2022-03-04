/*
to build a house we need at least three triangles. Let's call them T1, T2 and T3.
Each triangle is defined by three points. Then we'll have:
T1 = (a, b, c)
T2 = (b, d, c)
T3 = (c, d, e)
And each point is defined by two coordinates:
a = (xa, -1)
b = (xb, -1)
c = (xa, yc)
d = (xb, yc)
e = (xe, ye)
Also note that:
xb = xa + k, with k > 0
xe = xb - (xb - xa)/2
ye = yc + k, with k > 0
*/

float xa = 0.2f;
float xb = -0.2f;
float yc = 0.3f;
float xe = xb - (xb - xa)/2;
float ye = yc - 0.2f;

Triangle(xa, 1,  xb, 1,  xa, yc,  0, 0, 1);            // T1
Triangle(xb, 1,  xb, yc,  xa, yc,  0, 0, 1);           // T2
Triangle(xa+0.05, yc,  xb-.05, yc,  xe, ye,  1, 0, 0); // T3

/*
Still, we're missing the door and the windows.
Let's add them. Let's call them W1 and W2. We'll need to add two triangles for each window, plus another two for the door.
Starting from the door (let's call it D1), it needs to be centered in the house:
D1 = (T4, T5)
W1 = (T6, T7)
W2 = (T8, T9)
*/

Triangle(xa - 0.1,  yc + 0.03,  xa - 0.03,  yc + 0.03,  xa - 0.03,  yc + 0.1,  1, 1, 0); // T4
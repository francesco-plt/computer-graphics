# Basic Transformations

## Translation

A translation matrix can be used to move an object in a particular direction. The translation matrix is of the form:

```
1 0 0 Tx
0 1 0 Ty
0 0 1 Tz
0 0 0  1
```

Where $T_x$, $T_y$, and $T_z$ are the translation values in the $x$, $y$, and $z$ directions respectively. To apply a translation to a point $(x, y, z)$, the point is represented as a column vector and the translation matrix is multiplied on the left:
$$
p' = M \cdot p
$$

## Rotation

A rotation matrix can be used to rotate an object around a particular axis. The rotation matrix is of the form:

```
cos(θ) -sin(θ) 0 0
sin(θ)  cos(θ) 0 0
   0       0   1 0
   0       0   0 1
```

Where $\theta$ is the angle of rotation. To rotate an object around the x-axis, the matrix would be:

```
1       0       0       0
0  cos(θ) -sin(θ)  			0
0  sin(θ)  cos(θ)  			0
0       0       0       1
```

and around the y-axis:

```
cos(θ)				0  sin(θ)				0
   0          1       0       0
-sin(θ)       0  cos(θ)       0
   0          0       0       1
```

## Scaling

A scaling matrix can be used to scale an object in a particular direction. The scaling matrix is of the form:

```
Sx 0  0  0
0  Sy 0  0
0  0  Sz 0
0  0  0  1
```

Where $S_x$, $S_y$, and $S_z$ are the scaling values in the $x$, $y$, and $z$ directions respectively. To apply a scaling to a point $(x, y, z)$, the point is represented as a column vector and the scaling matrix is multiplied on the left:
$$
p' = M \cdot p
$$

## Shear

A shear matrix can be used to skew an object in a particular direction. The shear matrix is of the form:

```
1  kx 0  0
ky 1  0  0
0  0  1  0
0  0  0  1
```

Where $k_x$ and $k_y$ are the shear values in the x and y directions respectively. To apply a shear to a point $(x, y, z)$, the point is represented as a column vector and the shear matrix is multiplied on the left:
$$
p' = M \cdot p
$$
It's important to note that the transformation matrices are applied in the order they are composed, meaning that the translation matrix will be applied first, then the rotation matrix, etc.
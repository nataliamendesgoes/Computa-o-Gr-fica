#ifndef CLIPPINGVOLUMETRICO_H
#define CLIPPINGVOLUMETRICO_H
#include <QRect>

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
const int NEAR = 16;
const int FAR = 32;

int computeOutCode(double x, double y, double z, double xmin, double ymin, double zmin, double xmax, double ymax, double zmax);
bool cohenSutherlandClip3D(double xmin, double ymin, double zmin, double xmax, double ymax, double zmax,
                           double& x1, double& y1, double& z1, double& x2, double& y2, double& z2);
#endif // CLIPPINGVOLUMETRICO_H



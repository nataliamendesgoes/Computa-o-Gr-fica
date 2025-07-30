#include "clippingvolumetrico.h"
#include <QRect>



int computeOutCode(double x, double y, double z, double xmin, double ymin, double zmin, double xmax, double ymax, double zmax) {

    const int INSIDE = 0;
    const int LEFT = 1;
    const int RIGHT = 2;
    const int BOTTOM = 4;
    const int TOP = 8;
    const int NEAR = 16;
    const int FAR = 32;
    int code = INSIDE;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    if (z < zmin) code |= NEAR;
    else if (z > zmax) code |= FAR;
    return code;
}

bool cohenSutherlandClip3D(double xmin, double ymin, double zmin, double xmax, double ymax, double zmax,
                           double& x1, double& y1, double& z1, double& x2, double& y2, double& z2) {
    int code1 = computeOutCode(x1, y1, z1, xmin, ymin, zmin, xmax, ymax, zmax);
    int code2 = computeOutCode(x2, y2, z2, xmin, ymin, zmin, xmax, ymax, zmax);
    bool accept = false;

    while (true) {
        if ((code1 | code2) == 0) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int codeOut = code1 ? code1 : code2;
            double x, y, z;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
                z = z1 + (z2 - z1) * (ymax - y1) / (y2 - y1);
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
                z = z1 + (z2 - z1) * (ymin - y1) / (y2 - y1);
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
                z = z1 + (z2 - z1) * (xmax - x1) / (x2 - x1);
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
                z = z1 + (z2 - z1) * (xmin - x1) / (x2 - x1);
            } else if (codeOut & FAR) {
                x = x1 + (x2 - x1) * (zmax - z1) / (z2 - z1);
                y = y1 + (y2 - y1) * (zmax - z1) / (z2 - z1);
                z = zmax;
            } else if (codeOut & NEAR) {
                x = x1 + (x2 - x1) * (zmin - z1) / (z2 - z1);
                y = y1 + (y2 - y1) * (zmin - z1) / (z2 - z1);
                z = zmin;
            }

            if (codeOut == code1) {
                x1 = x; y1 = y; z1 = z;
                code1 = computeOutCode(x1, y1, z1, xmin, ymin, zmin, xmax, ymax, zmax);
            } else {
                x2 = x; y2 = y; z2 = z;
                code2 = computeOutCode(x2, y2, z2, xmin, ymin, zmin, xmax, ymax, zmax);
            }
        }
    }
    return accept;
}

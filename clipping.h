// clipping.h
#ifndef CLIPPING_H
#define CLIPPING_H
#include <QRect>


const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000


int computeCode(double x, double y, double xmin, double ymin, double xmax, double ymax);

bool cohenSutherlandClip(double xmin, double ymin, double xmax, double ymax,
                         double& x1, double& y1, double& x2, double& y2);
bool clippingCohenSutherland(double& x1, double& y1, double& x2, double& y2, const QRect& viewport);

#endif // CLIPPING_H

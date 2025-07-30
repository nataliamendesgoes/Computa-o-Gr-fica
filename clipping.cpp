// clipping.cpp
#include "clipping.h"
#include <QRect>

bool clippingCohenSutherland(double& x1, double& y1, double& x2, double& y2, const QRect& viewport) {
    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000

    auto computeOutCode = [&viewport](double x, double y) {
        int code = INSIDE;
        if (x < viewport.left()) code |= LEFT;
        else if (x > viewport.right()) code |= RIGHT;
        if (y < viewport.top()) code |= BOTTOM;
        else if (y > viewport.bottom()) code |= TOP;
        return code;
    };

    int outCode1 = computeOutCode(x1, y1);
    int outCode2 = computeOutCode(x2, y2);

    while (true) {
        if (!(outCode1 | outCode2)) {
            return true;
        } else if (outCode1 & outCode2) {
            return false;
        } else {

            double x, y;
            int outCodeOut = outCode1 ? outCode1 : outCode2;

            if (outCodeOut & TOP) {
                x = x1 + (x2 - x1) * (viewport.top() - y1) / (y2 - y1);
                y = viewport.top();
            } else if (outCodeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (viewport.bottom() - y1) / (y2 - y1);
                y = viewport.bottom();
            } else if (outCodeOut & RIGHT) {
                y = y1 + (y2 - y1) * (viewport.right() - x1) / (x2 - x1);
                x = viewport.right();
            } else if (outCodeOut & LEFT) {
                y = y1 + (y2 - y1) * (viewport.left() - x1) / (x2 - x1);
                x = viewport.left();
            }

            if (outCodeOut == outCode1) {
                x1 = x;
                y1 = y;
                outCode1 = computeOutCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                outCode2 = computeOutCode(x2, y2);
            }
        }
    }
}

int computeCode(double x, double y, double xmin, double ymin, double xmax, double ymax) {
    int code = INSIDE;

    if (x < xmin) {
        code |= LEFT;
    } else if (x > xmax) {
        code |= RIGHT;
    }
    if (y < ymin) {
        code |= BOTTOM;
    } else if (y > ymax) {
        code |= TOP;
    }

    return code;
}

bool cohenSutherlandClip(double xmin, double ymin, double xmax, double ymax,
                         double& x1, double& y1, double& x2, double& y2) {

    int code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
    int code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);

    bool accept = false;

    while (true) {
        if ((code1 | code2) == 0) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int codeOut = code1 ? code1 : code2;
            double x, y;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
            }
        }
    }

    return accept;
}

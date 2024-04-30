#ifndef VECT2D_H
#define VECT2D_H

#include <math.h>

class vect2d {
public:
    float x;
    float y;
public:
    float getAngle();
    vect2d operator+(vect2d const& obj);
    void normalize();
    float getMag();

    vect2d(float x, float y);
    vect2d(){}
};

#endif
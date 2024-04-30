#ifndef VECT2D_H
#define VECT2D_H

#include <math.h>

#define ZERO_VECT (vect2d(0,0))
#define NORMAL_VECT (vect2d(1,0))

class vect2d {
public:
    float x;
    float y;
public:
    float getAngle();
    vect2d operator+(vect2d const& obj);
    vect2d operator*(float const& obj);
    void normalize();
    float getMag();
    void rotate(float angle);

    vect2d(float x, float y);
    vect2d(){}
};

#endif
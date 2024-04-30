#include "vect2d.h"

vect2d vect2d::operator+(vect2d const& obj){
    vect2d value;
    value.x = obj.x + x;
    value.y = obj.y + y;
    return value;
}

float vect2d::getAngle(){
    return atan(y/x);
}

float vect2d::getMag(){
    return sqrt((x*x) + (y*y));
}

vect2d::vect2d(float x, float y) {
    this->x = x;
    this->y = y;
}

void vect2d::normalize(){
    float mag = this->getMag();
    x /= mag;
    y /= mag;
}

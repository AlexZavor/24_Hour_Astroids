#include "vect2d.h"

vect2d vect2d::operator+(vect2d const& obj){
    vect2d value;
    value.x = obj.x + x;
    value.y = obj.y + y;
    return value;
}

vect2d vect2d::operator*(float const &obj) {
    vect2d value;
    value.x = obj * x;
    value.y = obj * y;
    return value;
}

float vect2d::getAngle(){
    return atan(y/x);
}

float vect2d::getMag(){
    return sqrt((x*x) + (y*y));
}

void vect2d::rotate(float angle) {
    float px = x * cos(angle) - y * sin(angle);
    float py = x * sin(angle) + y * cos(angle);
    x = px;
    y = py;
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

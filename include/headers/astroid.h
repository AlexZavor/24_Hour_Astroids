#ifndef ASTROID_H
#define ASTROID_H

#include "vect2d.h"
#include "globals.h"
#include "SDL.h"

#define ASTROID_BASE_SIZE 100
#define ASTROID_BASE_SPEED 1
#define ASTROID_RESOLUTION 8

class astroid {
private:
    vect2d location;
    vect2d direction;
    int size;
public:
    bool isActive;
public:
    astroid(vect2d location, vect2d direction, int size);
    astroid();
    void drawAstroid(SDL_Renderer * renderer);
    void updateAstroid();
    bool isColliding(vect2d point);
    astroid explode();
private:
    int jankify(float number);
};


#endif
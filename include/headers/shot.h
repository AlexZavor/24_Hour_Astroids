#ifndef SHOT_H
#define SHOT_H

#include "vect2d.h"
#include "globals.h"
#include "SDL.h"

#define SHOT_SPEED 10
#define SHOT_LIFETIME 80

class shot {
private:
    vect2d location;
    vect2d direction;
    int lifetime;
public:
    bool isActive = false;
public:
    shot(vect2d location, vect2d direction);
    shot();
    void drawShot(SDL_Renderer * renderer);
    void updateShot();

    vect2d getLocation(){return location;}
};


#endif
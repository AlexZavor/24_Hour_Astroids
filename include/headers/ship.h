#ifndef SHIP_H
#define SHIP_H

#include "vect2d.h"
#include "SDL.h"

#define SHIP_HEIGHT 50
#define SHIP_WIDTH  25

class Ship
{
private:
    vect2d location;
    vect2d direction; 
public:
    Ship(vect2d locaiton);
    void DrawShip(SDL_Renderer* renderer);
};

#endif
#ifndef SHIP_H
#define SHIP_H

#include "vect2d.h"
#include "shot.h"
#include "SDL.h"
#include "globals.h"
#include "astroid.h"

#define SHIP_HEIGHT 40
#define SHIP_WIDTH  25
#define SHOT_NUM 5

#define SHIP_ROTATION 0.05f     // Ship angular speed in rad/sec
#define SHIP_SPEED 0.15f
#define FRICTION 0.99

class Ship {
private:
    vect2d location;
    vect2d velocity;

    // angle stored is /2 so atan works better. ha ha
    vect2d angle;
    float rotationalSpeed = 0;

    bool isDriving = false;

    shot shots[SHOT_NUM];
public:
    Ship(vect2d locaiton);
    void setRotation(float rot){rotationalSpeed = rot;}
    void setDriving(bool drv){isDriving = drv;}
    void setLocation(vect2d loc){location = loc;velocity = ZERO_VECT;}
    void drive();
    void fire();
    Ship rotate(float ang){angle.rotate(ang); return *this;}

    void drawShip(SDL_Renderer* renderer);
    void updateShip();
    int checkAstroidCollision(astroid* astroids, int maxAstroids);
    bool checkPlayerCollision(astroid* astroids, int maxAstroids);
    vect2d getPosition(){return location;}
};

#endif
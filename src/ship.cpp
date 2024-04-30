#include "ship.h"


Ship::Ship(vect2d location) {
    this->location = location;
    angle = vect2d(1,0);
}

void Ship::drive(){
    vect2d realAngle = NORMAL_VECT;
    realAngle.rotate(angle.getAngle()*2);
    velocity = velocity + (realAngle * SHIP_SPEED);
}

void Ship::drawShip(SDL_Renderer * renderer) {
    // Draws a ship with center at location. angle coming soon
    vect2d front = vect2d((SHIP_HEIGHT/2), 0);
    vect2d backLeft  = vect2d(-(SHIP_HEIGHT/2), -(SHIP_WIDTH/2));
    vect2d backRight = vect2d(-(SHIP_HEIGHT/2), (SHIP_WIDTH/2));

    front.rotate(angle.getAngle()*2);
    backLeft.rotate(angle.getAngle()*2);
    backRight.rotate(angle.getAngle()*2);

    front = front + location;
    backLeft = backLeft + location;
    backRight = backRight + location;

    SDL_RenderDrawLine(renderer, front.x, front.y,          backRight.x, backRight.y);
    SDL_RenderDrawLine(renderer, front.x, front.y,          backLeft.x, backLeft.y);
    SDL_RenderDrawLine(renderer, backRight.x, backRight.y,  backLeft.x, backLeft.y);
}

void Ship::updateShip() {
    angle.rotate(rotationalSpeed);
    if(isDriving){
        drive();
    }
    location = location + velocity;
    velocity = velocity * FRICTION;
}

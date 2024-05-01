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

void Ship::fire()
{
    for(int i = 0; i<SHOT_NUM; i++){
        if(!shots[i].isActive){
            shots[i] = shot(location, angle);
            break;
        }
    }
}

void Ship::drawShip(SDL_Renderer * renderer) {
    // Draws a ship with center at location.
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
    
    // Also draw shots
    for(int i = 0; i<SHOT_NUM; i++){
        if(shots[i].isActive){
            shots[i].drawShot(renderer);
        }
    }
}

void Ship::updateShip() {
    angle.rotate(rotationalSpeed);
    if(isDriving){
        drive();
    }
    location = location + velocity;
    velocity = velocity * FRICTION;
    location = location % vect2d(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Also update shots
    for(int i = 0; i<SHOT_NUM; i++){
        if(shots[i].isActive){
            shots[i].updateShot();
        }
    }
}

int Ship::checkAstroidCollision(astroid* astroids, int maxAstroids) {
    int hits = 0;
    // Astroid Loop
    for(int i = 0; i < maxAstroids; i++){
        if(astroids[i].isActive){
            // Shot loop
            for(int s = 0; s<SHOT_NUM; s++){
                if(shots[s].isActive){
                    // check collision
                    if(astroids[i].isColliding(shots[s].getLocation())){

                        shots[s].isActive = false;
                        hits++;
                        for(int j = 0; j < maxAstroids; j++){
                            if(!astroids[j].isActive){
                                astroids[j] = astroids[i].explode();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return hits;
}

bool Ship::checkPlayerCollision(astroid *astroids, int maxAstroids) {
    vect2d front = vect2d((SHIP_HEIGHT/2), 0);
    vect2d backLeft  = vect2d(-(SHIP_HEIGHT/2), -(SHIP_WIDTH/2));
    vect2d backRight = vect2d(-(SHIP_HEIGHT/2), (SHIP_WIDTH/2));

    front.rotate(angle.getAngle()*2);
    backLeft.rotate(angle.getAngle()*2);
    backRight.rotate(angle.getAngle()*2);

    front = front + location;
    backLeft = backLeft + location;
    backRight = backRight + location;

    // Astroid Loop
    for(int i = 0; i < maxAstroids; i++){
        if(astroids[i].isActive){
            // check collision
            if(astroids[i].isColliding(front)){
                return true;
            }else if(astroids[i].isColliding(backLeft)){
                return true;
            }else if(astroids[i].isColliding(backRight)){
                return true;
            }
        }
    }
    return false;
}

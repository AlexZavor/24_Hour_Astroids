#include "shot.h"

shot::shot(vect2d location, vect2d direction) {
    this->location = location;
    direction.normalize();
    this->direction = direction * SHOT_SPEED;
    isActive = true;
    lifetime = SHOT_LIFETIME;
}

shot::shot() {
    isActive = false;
}

void shot::drawShot(SDL_Renderer * renderer) {
    SDL_SetRenderDrawColor(renderer, SHOT_COLOR);
    SDL_RenderDrawLine(renderer, location.x+1, location.y, location.x-1, location.y);
    SDL_RenderDrawLine(renderer, location.x, location.y+1, location.x, location.y-1);
    SDL_SetRenderDrawColor(renderer, STANDARD_COLOR);
}

void shot::updateShot(){
    vect2d realDirection = NORMAL_VECT;
    realDirection.rotate(direction.getAngle()*2);
    realDirection = realDirection * direction.getMag();
    location = location + realDirection;

    location = location % vect2d(SCREEN_WIDTH, SCREEN_HEIGHT);

    lifetime--;
    if(lifetime <= 0){
        isActive = false;
    }
}

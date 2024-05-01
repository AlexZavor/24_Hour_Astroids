#include "astroid.h"

astroid::astroid(vect2d location, vect2d direction, int size) {
    this->location = location;
    this->direction = direction;
    this->size = size;
    isActive = true;
}

astroid::astroid() {
    isActive = false;
}

void astroid::drawAstroid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, ASTROID_COLOR);
    vect2d points[ASTROID_RESOLUTION];
    points[0] = NORMAL_VECT * (ASTROID_BASE_SIZE/size);
    for(int i = 1; i < ASTROID_RESOLUTION; i++){
        points[i] = points[i-1];
        points[i].rotate(TWOPI/ASTROID_RESOLUTION);
        SDL_RenderDrawLine(renderer, jankify(location.x+points[i-1].x), jankify(location.y+points[i-1].y), 
                                     jankify(location.x+points[i].x),   jankify(location.y+points[i].y));
    }
    SDL_RenderDrawLine(renderer, jankify(location.x+points[ASTROID_RESOLUTION-1].x), jankify(location.y+points[ASTROID_RESOLUTION-1].y), 
                                    jankify(location.x+points[0].x), jankify(location.y+points[0].y));
    SDL_SetRenderDrawColor(renderer, STANDARD_COLOR);
}

void astroid::updateAstroid() {
    vect2d movement = NORMAL_VECT;
    movement.rotate(direction.getAngle() * 2);
    movement = movement * ASTROID_BASE_SPEED * size;
    location = location + movement;
    location = location % vect2d(SCREEN_WIDTH, SCREEN_HEIGHT);
}

bool astroid::isColliding(vect2d point)
{
    if((location-point).getMag() < (ASTROID_BASE_SIZE/size)){
        return true;
    }
    return false;
}

astroid astroid::explode()
{
    size++;
    if(size > ASTROID_MAX_SIZE){
        isActive = false;
    }
    astroid another = *this;
    another.direction = NORMAL_VECT.rotate (direction.getAngle()+HALFPI);
    return another;
}

int astroid::jankify(float number) {
    return ((int)(number / JANK_CONSTANT)) * JANK_CONSTANT;
}

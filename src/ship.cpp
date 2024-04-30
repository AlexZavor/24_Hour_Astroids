#include "ship.h"


Ship::Ship(vect2d location) {
    this->location = location;
}

void Ship::DrawShip(SDL_Renderer * renderer) {
    // Draws a ship with center at location. angle coming soon
    SDL_RenderDrawLine(renderer, this->location.x, this->location.y-(SHIP_HEIGHT/2), this->location.x+(SHIP_WIDTH/2), this->location.y+(SHIP_HEIGHT/2));
    SDL_RenderDrawLine(renderer, this->location.x, this->location.y-(SHIP_HEIGHT/2), this->location.x-(SHIP_WIDTH/2), this->location.y+(SHIP_HEIGHT/2));
    SDL_RenderDrawLine(renderer, this->location.x-(SHIP_WIDTH/2), this->location.y+(SHIP_HEIGHT/2), this->location.x+(SHIP_WIDTH/2), this->location.y+(SHIP_HEIGHT/2));
}
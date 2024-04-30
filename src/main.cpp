#include <stdio.h>
#include "globals.h"
#include "vect2d.h"
#include "ship.h"
#include "SDL.h"
#include "SDL_ttf.h"


bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer, SDL_Texture** texture){
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}
	//Create window
	*window = SDL_CreateWindow( "Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( *window == NULL ) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return 0;
	}
	//Create vsynced renderer for window
	*renderer = SDL_CreateRenderer( *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( *renderer == NULL ) {
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
	}
	//Create texture to render pixels to.
	*texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if( *texture == NULL ) {
		printf( "Texture could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	TTF_Init();

	return true;
}

bool closeSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture){
	//Destroy window
	if( texture != NULL ) {
		SDL_DestroyTexture( texture );
	}
	//Destroy renderer
	if( renderer != NULL ) {
		SDL_DestroyRenderer(renderer);
	}
	//Destroy window
	if( window != NULL ) {
		SDL_DestroyWindow( window );
	}
	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
	return true;
}

int main(int argc, char* argv[]) {
	// The window we'll be rendering to
	SDL_Window* window = NULL;
	// The window renderer
	SDL_Renderer* renderer = NULL;
	// The texture to render to
    SDL_Texture* texture = NULL;
	// Event handler
	SDL_Event e;

	bool quit = false;

	if(initializeSDL(&window, &renderer, &texture)){
		while(!quit){

			// Uint64 start = SDL_GetPerformanceCounter();

			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 ) {
				//User requests quit
				if( e.type == SDL_QUIT ) {
					quit = true;
				}
				//User presses a key
				else if( e.type == SDL_KEYDOWN ) {
					switch( e.key.keysym.sym ) {
						case SDLK_UP:
						break;
					}
				}
				else if( e.type == SDL_KEYUP ) {
					switch( e.key.keysym.sym ) {
						case SDLK_UP:
						break;
					}
				}
			}
			

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			int mouseX;
			int mouseY;

			SDL_GetMouseState(&mouseX, &mouseY);
			ship
			// vect2d mouse = vect2d(mouseX-SCREEN_WIDTH/2, mouseY-SCREEN_HEIGHT/2);

			printf("loc: %f,%f ang: %f mag: %f \n", mouse.x, mouse.y, mouse.getAngle(), mouse.getMag());
			


			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderDrawLine(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, mouseX, mouseY);

			SDL_RenderPresent( renderer );

			
			// Uint64 end = SDL_GetPerformanceCounter();
			// float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
			// printf("%f ms\n", elapsedMS);
		}
	}

	closeSDL(window, renderer, texture);

	return 0;
}
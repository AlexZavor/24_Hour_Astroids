#include <stdio.h>
#include <time.h>
#include <random>
#include "globals.h"
#include "vect2d.h"
#include "ship.h"
#include "astroid.h"
#include "SDL.h"
#include "SDL_ttf.h"


Ship player = Ship(vect2d(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
int astroidMax = ASTROID_NUMBER * pow(2, ASTROID_MAX_SIZE);
astroid astroids[ASTROID_NUMBER * (int)pow(2, ASTROID_MAX_SIZE)];

int lives = STARTING_LIVES;
int score = 0;
bool invincible = false;
int invincibleTimer = 0;

bool quit = false;
bool menu = true;
bool gameOver = false;


bool initializeSDL(SDL_Window** window, SDL_Renderer** renderer){
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

	TTF_Init();

	return true;
}

bool closeSDL(SDL_Window* window, SDL_Renderer* renderer){
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

void drawUI(int lives, int score, SDL_Renderer* renderer){
	SDL_SetRenderDrawColor(renderer, LIVES_COLOR);
	for (int life = 1; life < lives; life++)
	{
		Ship(vect2d(50*life,50)).rotate(-HALFPI/2).drawShip(renderer);
	}

	SDL_SetRenderDrawColor(renderer, SCORE_COLOR);
	static TTF_Font* minecraft = TTF_OpenFont(FONT_LOCATION, 16);

	std::string scoreStr = std::to_string(score);
	SDL_Color scoreColor = {SCORE_COLOR};

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(minecraft, scoreStr.c_str(), scoreColor); 

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 1000;  //controls the rect's x coordinate 
	Message_rect.y = 25; // controls the rect's y coordinte
	Message_rect.w = scoreStr.length()*32; // controls the width of the rect
	Message_rect.h = 64; // controls the height of the rect
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	// Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void fillAstroids(){
	for(int i = 0; i < ASTROID_NUMBER; i++){
		do{
		astroids[i] = astroid(vect2d(rand()%SCREEN_WIDTH, rand()%SCREEN_HEIGHT),
						      NORMAL_VECT.rotate((rand()%((int)(TWOPI*100)))/100.0),
							  1);
		} while (astroids[i].isColliding(player.getPosition()));
	}
}

void emptyAstroids(){
	for(int i = 0; i < astroidMax; i++){
		astroids[i] = astroid();
	}
}

void runGameLoop(SDL_Event e, SDL_Renderer* renderer){
	// Handle events on queue
	while( SDL_PollEvent( &e ) != 0 ) {
		//User requests quit
		if( e.type == SDL_QUIT ) {
			quit = true;
		}
		//User presses a key
		else if( e.type == SDL_KEYDOWN ) {
			switch( e.key.keysym.sym ) {
				case SDLK_UP:
					player.setDriving(true);
				break;
				case SDLK_RIGHT:
					player.setRotation(SHIP_ROTATION);
				break;
				case SDLK_LEFT:
					player.setRotation(-SHIP_ROTATION);
				break;
				case SDLK_SPACE:
					player.fire();
				break;
				case SDLK_ESCAPE:
					player.setLocation(vect2d(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
				break;
			}
		}
		else if( e.type == SDL_KEYUP ) {
			switch( e.key.keysym.sym ) {
				case SDLK_UP:
					player.setDriving(false);
				break;
				case SDLK_RIGHT:
					player.setRotation(0);
				break;
				case SDLK_LEFT:
					player.setRotation(0);
				break;
			}
		}
	}

	// ----- Update -----
	// Update Astroids
	int astroidCheck = 0;
	for(int i = 0; i < astroidMax; i++){
		if(astroids[i].isActive){
			astroidCheck++;
			astroids[i].updateAstroid();
		}
	}
	if(astroidCheck == 0){
		fillAstroids();
	}

	// Update Ship
	player.updateShip();
	score += player.checkAstroidCollision(astroids, astroidMax) * SCORE_MULTIPLER;

	// Invinicibility logic (sm)
	if(invincible){
		invincibleTimer--;
		if(invincibleTimer == 0){
			invincible = false;
		}
	}else{
		bool hit = player.checkPlayerCollision(astroids, astroidMax);
		if(hit){
			lives--;
			invincible = true;
			invincibleTimer = INVINCIBILITY_TIME;
			if(lives == 0){
				menu = true;
				gameOver = true;
			}
		}
	}

	// ----- Drawing -----
	SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);
	SDL_RenderClear(renderer);

	// Draw Astroids
	SDL_SetRenderDrawColor(renderer, STANDARD_COLOR);
	for(int i = 0; i < astroidMax; i++){
		if(astroids[i].isActive){
			astroids[i].drawAstroid(renderer);
		}
	}
	
	// Draw player
	if(invincibleTimer%40 < 20){
		player.drawShip(renderer);
	}

	// Draw UI
	drawUI(lives, score, renderer);
}

void illmenyou(SDL_Event e, SDL_Renderer* renderer){
	// Handle events on queue
	while( SDL_PollEvent( &e ) != 0 ) {
		//User requests quit
		if( e.type == SDL_QUIT ) {
			quit = true;
		}
		//User presses a key
		else if( e.type == SDL_KEYDOWN ) {
			switch( e.key.keysym.sym ) {
				case SDLK_SPACE:
					lives = STARTING_LIVES;
					score = 0;
					invincible = false;
					invincibleTimer = 0;
					menu = false;
					player.setLocation(vect2d(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
					player.setRotation(0);
					player.setDriving(false);
					emptyAstroids();
					fillAstroids();
				break;
			}
		}
	}

	// ----- Drawing -----
	SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR);
	SDL_RenderClear(renderer);

	static TTF_Font* minecraft = TTF_OpenFont(FONT_LOCATION, 16);
	SDL_Color scoreColor = {STANDARD_COLOR};

	std::string scoreStr = "Astroids";

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(minecraft, scoreStr.c_str(), scoreColor); 

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 500;  //controls the rect's x coordinate 
	Message_rect.y = 192; // controls the rect's y coordinte
	Message_rect.w = scoreStr.length()*32; // controls the width of the rect
	Message_rect.h = 64; // controls the height of the rect
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	// Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	

	scoreStr = "Press space to play";

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	surfaceMessage =
		TTF_RenderText_Solid(minecraft, scoreStr.c_str(), scoreColor); 

	// now you can convert it into a texture
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	Message_rect.x = 300;  //controls the rect's x coordinate 
	Message_rect.y = 256; // controls the rect's y coordinte
	Message_rect.w = scoreStr.length()*32; // controls the width of the rect
	Message_rect.h = 64; // controls the height of the rect
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	// Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	// Draw UI
	drawUI(lives, score, renderer);
}

int main(int argc, char* argv[]) {
	std::srand(time(NULL));
	// The window we'll be rendering to
	SDL_Window* window = NULL;
	// The window renderer
	SDL_Renderer* renderer = NULL;
	// Event handler
	SDL_Event e;

	if(initializeSDL(&window, &renderer)) {
		while(!quit){
			if(menu){
				illmenyou(e, renderer);
			}else{
				runGameLoop(e, renderer);
			}

			// ----- Present -----
			SDL_RenderPresent( renderer );
		}
	}

	closeSDL(window, renderer);

	return 0;
}
#include "RRApp.h"
#include "RRMap.h"
#include <SDL2/SDL.h>
#include <iostream>

RRApp::RRApp(SDL_Window *window, SDL_Renderer *renderer){
	finish = false;
	this->window = window;
	this->renderer = renderer;
	map = new RRMap(this, window,renderer);
	speed = 0;
} 

int RRApp::getSpeed(){
	return speed;
}

void RRApp::updateSpeed(){
	if(keyStatus[2] == 0)
		if(keyStatus[3] == 0)
			speed = 0;
		else
			speed = -1;
	else
		if(keyStatus[3]==0)
			speed = 1;
		else
			speed = 0;
}



void RRApp::mainLoop(){
	SDL_Event event;
	while (SDL_WaitEvent(&event) && !finish) {
		eventHandler(event);
	}
}

void RRApp::updateGame(){
	map->update();
}

void RRApp::renderGame(){
	SDL_RenderClear(renderer);
	map->render();
	SDL_RenderPresent(renderer);
}

void RRApp::eventHandler(SDL_Event &event){
	switch (event.type)	{
		case SDL_QUIT:
			finish = true;
			break;
		case SDL_USEREVENT:
    		updateGame();
    		renderGame();
    		break;
    	case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			    case SDLK_LEFT:
			      keyStatus[0] = 1;
			      break;
			    case SDLK_RIGHT:
			      keyStatus[1] = 1;
			      break;
			    case SDLK_UP:
			      keyStatus[2] = 1;
			      break;
			    case SDLK_DOWN:
			      keyStatus[3] = 1;
			      break;
			}
			updateSpeed();
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			    case SDLK_LEFT:
			      keyStatus[0] = 0;
			      break;
			    case SDLK_RIGHT:
			      keyStatus[1] = 0;
			      break;
			    case SDLK_UP:
			      keyStatus[2] = 0;
			      break;
			    case SDLK_DOWN:
			      keyStatus[3] = 0;
			      break;
			}
			updateSpeed();
			break;
		default:
			break;
	}
}

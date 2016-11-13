#include "RRApp.h"
#include <SDL2/SDL.h>
#include <iostream>

RRApp::RRApp(SDL_Window *window, SDL_Renderer *renderer){
	finish = false;
	this->window = window;
	this->renderer = renderer;
	map = new RRMap(window,renderer);
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
		default:
			break;
	}
}

#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>

RRMap::RRMap(SDL_Window *window, SDL_Renderer *renderer):window(window), renderer(renderer){
	SDL_GetWindowSize(window, &width, &height);
	screen.x = screen.y = 0;
	screen.h = height;
	screen.w = width;
	SDL_Surface *surface = IMG_Load("img/map01.png");
	img1 = SDL_CreateTextureFromSurface(renderer, surface);
	size1.x = size1.y = 0;
	SDL_QueryTexture(img1, NULL, NULL, &size1.w, &size1.h);
	if(img1==NULL)
		std::cout<<"error "<< IMG_GetError();
	rect1 = screen;
}

void RRMap::render(){
	SDL_RenderCopy(renderer, img1, &rect1, &screen);
}

void RRMap::update(){
	rect1.y+=1;
}

#include "RRApp.h"
#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>
#include <cstdio>

const static int numMaps = 2;
const static char mapfile[numMaps][40]={
	"img/mapcolortree.bmp",
	"img/mapcolor2tree.bmp"
};

RRMap::RRMap(RRApp *app, SDL_Window *window, SDL_Renderer *renderer): app(app), window(window), renderer(renderer){
	SDL_GetWindowSize(window, &width, &height);
	screen.x = screen.y = 0;
	screen.h = height;
	screen.w = width;
	for(int i=0;i<numMaps;i++){
		SDL_Surface *surface = IMG_Load(mapfile[i]);
		if(surface==NULL)
			std::cout<<"error "<< IMG_GetError();
		mapimg.push_back(SDL_CreateTextureFromSurface(renderer, surface));
		if(mapimg[0]==NULL)
			std::cout<<"error "<< IMG_GetError();
	}
	size.x = size.y = 0;
	SDL_QueryTexture(mapimg[0], NULL, NULL, &size.w, &size.h);


	view_height = screen.h*size.w/screen.w;
	rect1.y = size.h - view_height;
	rect1.w = size.w;
	rect1.h = screen.h *size.w/screen.w;
	rect1.x = 0;
	
	img1 = mapimg[0];
	img2 = mapimg[0];
	
	SDL_Surface *surface = IMG_Load("img/bridge.bmp");
	bridge = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_QueryTexture(bridge, NULL, NULL, &br.w, &br.h);
	br.x = br.y = 0; 
}



void RRMap::render(){
	if(rect1.y>=0){
		SDL_RenderCopy(renderer, img1, &rect1, &screen);
	}
	else{		
		SDL_Rect screen_down, screen_up;
		screen_down = screen;
		screen_up = screen; 
		screen_up.h = (-rect1.y*screen.w/size.w);
		screen_down.y = screen_up.h;
		screen_down.h = screen.h-screen_up.h;
		SDL_Rect rect3 = rect1;
		rect3.y = 0;
		rect3.h = view_height+rect1.y;
		printf("%d %d %d %d ", rect2.x, rect2.y, rect2.w, rect2.h);
		printf("%d %d %d %d ", screen_up.x, screen_up.y, screen_up.w, screen_up.h); 
		printf("%d %d %d %d ", rect3.x, rect3.y, rect3.w, rect3.h);
		printf("%d %d %d %d \n", screen_down.x, screen_down.y, screen_down.w, screen_down.h); 
		SDL_RenderCopy(renderer, img1, &rect3, &screen_down);
		SDL_RenderCopy(renderer, img2, &rect2, &screen_up);
	}
}

void RRMap::update(){
	int speed = app->getSpeed();
	switch(speed){
		case 0:
			rect1.y-=2;
			break;
		case 1:
			rect1.y-=4;
			break;
		case -1:
			rect1.y-=1;
			break;
		default:
			break;
	}
	
	if(rect1.y<0){
		rect2 = rect1;
		rect2.y = size.h +rect1.y;
		rect2.h = -rect1.y;
		if(rect2.y+view_height<size.h){
			std::cout<< "change to 2nd" <<std::endl; 
			rect2.h = rect1.h;
			rect1 = rect2;
			img1 = img2;
			img2 = mapimg[0];
		}
	}

}

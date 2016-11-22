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
	}
//	size.x = size.y = 0;
//	SDL_QueryTexture(mapimg[0], NULL, NULL, &size.w, &size.h);


//	view_height = screen.h*size.w/screen.w;
//	rect1.y = size.h - view_height;
//	rect1.w = size.w;
//	rect1.h = screen.h *size.w/screen.w;
//	rect1.x = 0;
	mapindex = 0;
	map1 = new MapSection(mapimg[mapindex++],0, screen);
	
	SDL_Surface *surface = IMG_Load("img/bridge.bmp");
	bridgeimg = SDL_CreateTextureFromSurface(renderer, surface);
	
}



void RRMap::render(){
	if(map1){
		printf("%d %d %d %d\n", map1->src()->y, map1->src()->h, map1->dst()->y,map1->dst()->h);
	}
	if(bridge){
		printf("%d %d %d %d\n", bridge->src()->y, bridge->src()->h, bridge->dst()->y,bridge->dst()->h);
	}
	if(map1)
		SDL_RenderCopy(renderer, map1->getTexture(), map1->src(), map1->dst());
	if(bridge)
		SDL_RenderCopy(renderer, bridge->getTexture(), bridge->src(), bridge->dst());
	if(map2)
		SDL_RenderCopy(renderer, map2->getTexture(), map2->src(), map2->dst());
						
//	if(rect1.y>=0){
//		SDL_RenderCopy(renderer, map1, &rect1, &screen);
//	}
//	else{		
//		SDL_Rect screen_down, screen_up;
//		screen_down = screen;
//		screen_up = screen; 
//		screen_up.h = (-rect1.y*screen.w/size.w);
//		screen_down.y = screen_up.h;
//		screen_down.h = screen.h-screen_up.h;
//		SDL_Rect rect3 = rect1;
//		rect3.y = 0;
//		rect3.h = view_height+rect1.y;
//		printf("%d %d %d %d ", rect2.x, rect2.y, rect2.w, rect2.h);
//		printf("%d %d %d %d ", screen_up.x, screen_up.y, screen_up.w, screen_up.h); 
//		printf("%d %d %d %d ", rect3.x, rect3.y, rect3.w, rect3.h);
//		printf("%d %d %d %d \n", screen_down.x, screen_down.y, screen_down.w, screen_down.h); 
//		SDL_RenderCopy(renderer, map1, &rect3, &screen_down);
//		SDL_RenderCopy(renderer, map2, &rect2, &screen_up);
//	}
}

void RRMap::update(){
	int speed = app->getSpeed();
	switch(speed){
		case 0:
			if(map1)
				map1->move(2);
			if(bridge)
				bridge->move(2);
			if(map2)
				map2->move(2);
			break;
		case 1:
			if(map1)
				map1->move(8);
			if(bridge)
				bridge->move(8);
			if(map2)
				map2->move(8);
			break;
		case -1:
			if(map1)
				map1->move(1);
			if(bridge)
				bridge->move(1);
			if(map2)
				map2->move(1);
			break;
		default:
			break;
	}
	
	if(map1 && map1->inScreen()==0 && bridge ==NULL){
		cout << "create bridge"<<endl;
		bridge = new Bridge(bridgeimg, screen.h, screen);
	}else if(map1 && map1->inScreen()==0 && bridge->inScreen()==0 && !map2){
		map2 = new MapSection(mapimg[mapindex++],screen.h, screen);
		mapindex = mapindex %numMaps;
	}else if(map1 && map1->inScreen()==-1){
		delete map1;
		printf("delete map1\n");
		map1 = NULL;
	}else if(!map1 &&bridge->inScreen()==-1){
		delete bridge;
		bridge = NULL;
		map1 = map2;
		map2 = NULL;
	}
	

}


MapSection::MapSection(SDL_Texture *txt, int ypos, SDL_Rect screen): img(txt), screen(screen){
	size.x = size.y = 0;
	SDL_QueryTexture(txt, NULL, NULL, &size.w, &size.h);
	printf("size h %d", size.h);
	
	scale = 800.0/600;
	
	
	size.w = size.w*scale;
	size.h = size.h*scale;
	this->ypos = size.h+ypos-screen.h;
	updateRect();
} 

SDL_Texture *MapSection::getTexture(){
	return img;
}


void MapSection::move(int deltay){
	ypos-=deltay;	
	updateRect();
}

int MapSection::inScreen(){
	if(ypos+screen.h<0)
		return -1;
	if(ypos<0)
		return 0;
	return 1;
}

SDL_Rect *MapSection::src(){

	return &src_rect;
}

SDL_Rect *MapSection::dst(){

	return &dst_rect;
}

void MapSection::updateRect(){
	src_rect.x = 0;
	src_rect.y = ypos;
	src_rect.w = screen.w;
	src_rect.h = screen.h;
	dst_rect = screen;
	if(src_rect.y<0){
		dst_rect.y = -src_rect.y;
		dst_rect.h = dst_rect.h + src_rect.y;
		src_rect.h = src_rect.h+src_rect.y;
		src_rect.y = 0;
	}
	if(src_rect.y+src_rect.h>size.h){
		dst_rect.h = size.h-src_rect.y;
		src_rect.h = size.h-src_rect.y;
	}
	src_rect.y = src_rect.y / scale;
	src_rect.h = src_rect.h / scale;
	src_rect.w = src_rect.w / scale;
}

Bridge::Bridge(SDL_Texture *txt, int ypos, SDL_Rect screen):MapSection(txt,ypos,screen){
	
}

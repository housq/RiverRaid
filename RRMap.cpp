#include "RRApp.h"
#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>
#include <fstream>
#include <cstdio>

const static int numMaps = 2;
const static char mapfile[numMaps][100]={
	"img/mapfinaltree.bmp",
	"img/mapfinal2tree.bmp"
};

const static char mapboundary[numMaps][100]={
	"img/mapfinal.txt",
	"img/mapfinal2.txt"
};

const int boundingBoxHeight = 100;

RRMap::RRMap(RRApp *app, SDL_Window *window, SDL_Renderer *renderer): app(app), window(window), renderer(renderer){
	SDL_GetWindowSize(window, &width, &height);
	screen.x = screen.y = 0;
	screen.h = height;
	screen.w = width;
	for(int i=0;i<numMaps;i++){
		SDL_Surface *surface = IMG_Load(mapfile[i]);
		if(surface==NULL)
			std::cout<<"error "<< IMG_GetError();
		SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, surface);
		if(txt==NULL)
			std::cout<<"error "<< IMG_GetError();
		maps.push_back(new MapSection(renderer, txt,mapboundary[i], 0,screen));
	}
	mapindex = 0;
	map1 = maps[0];	



	
	SDL_Surface *surface = IMG_Load("img/bridge.bmp");
	bridgeimg = SDL_CreateTextureFromSurface(renderer, surface);
}



void RRMap::render(){
	if(map1)
		map1->render();
	if(map2)
		map2->render();
	if(bridge)
		bridge->render();
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
		bridge = new Bridge(renderer, bridgeimg, screen.h+map1->ypos, screen);
	}else if(map1 && bridge && bridge->inScreen()==0 && map2 ==NULL){
		mapindex = (mapindex+1) %numMaps;
		map2 = maps[mapindex];
		map2->setYpos(screen.h+bridge->ypos);
	}
	else if(map1 && map1->inScreen()==-1){
		map1 = NULL;
	}else if(!map1 &&bridge->inScreen()==-1){
		delete bridge;
		bridge = NULL;
		map1 = map2;
		map2 = NULL;
	}
}

vector<SDL_Rect> *RRMap::boundingBoxMap1(){
	if(map1)
		return &map1->boundaries;
	else
		return NULL;
}

vector<SDL_Rect> *RRMap::boundingBoxMap2(){
	if(map2)
		return &map2->boundaries;
	else
		return NULL;
}

SDL_Rect RRMap::boundingBoxBridge(){
	if(bridge && !bridge->destroyed){
		return *bridge->dst();
	}else{
		SDL_Rect rect;
		rect.h = -1;
	}
}

void RRMap::destroyBridge(){
	if(bridge){
		bridge->destroy();
	}
}

MapSection::MapSection(SDL_Renderer *renderer, SDL_Texture *txt, int ypos, SDL_Rect screen): renderer(renderer), img(txt), screen(screen){
	size.x = size.y = 0;
	SDL_QueryTexture(txt, NULL, NULL, &size.w, &size.h);
	
	scale = 1;
	size.w = size.w*scale;
	size.h = size.h*scale;
	
	this->ypos = size.h+ypos-screen.h;
	updateRect();
}

MapSection::MapSection(SDL_Renderer *renderer, SDL_Texture *txt, const char *boundaryFile, int ypos, SDL_Rect screen): MapSection(renderer, txt,ypos,screen){
	ifstream bounds(boundaryFile);
	SDL_Rect boundingbox;
	boundingbox.h = boundingBoxHeight;
	boundingbox.y = 0;
	for(int i=0; i<size.h/boundingBoxHeight; i++){
		int minl,maxl,minr,maxr;
		bounds >>minl>>maxl>>minr>>maxr;
		boundingbox.x = 0;
		boundingbox.w = maxl;
		boundaries.push_back(boundingbox);
		boundaryPos.push_back(boundingbox.y);
		boundingbox.x = minr;
		boundingbox.w = size.w-minr-1;
		boundaries.push_back(boundingbox);
		boundaryPos.push_back(boundingbox.y);
		boundingbox.y +=boundingBoxHeight;
	}
	updateRect();
} 

void MapSection::render(){
	SDL_RenderCopy(renderer, getTexture(), src(), dst());
//	for(int i=0;i<boundaries.size();i++){
//		SDL_RenderDrawRect(renderer,&boundaries[i]);
//	}
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
	
	for(int i=0;i<boundaries.size();i++){
		boundaries[i].y = boundaryPos[i]-ypos;
	}
}

void MapSection::setYpos(int ypos){
	this->ypos = size.h+ypos-screen.h;
	updateRect();
}

Bridge::Bridge(SDL_Renderer *renderer, SDL_Texture *txt, int ypos, SDL_Rect screen):MapSection(renderer, txt,ypos,screen){
	destroyed = false;
}

void Bridge::destroy(){
	destroyed = true;
}

void Bridge::render(){
	SDL_Rect src = *this->src();
	SDL_Rect dst = *this->dst();
	if(!destroyed)
		SDL_RenderCopy(renderer, getTexture(), &src, &dst);
	else{
		src.w = 200;
		dst.w = 200;
		SDL_RenderCopy(renderer, getTexture(), &src, &dst);
		src.x = 600;
		dst.x = 600;
		SDL_RenderCopy(renderer, getTexture(), &src, &dst);
	}
		
}




#ifndef RR_MAP_H
#define RR_MAP_H

#include "SDL2/SDL.h"
#include <memory>
#include <list>
#include <vector>

#include "Asset.h"

class RRApp;
//class Projectile;
//class Player;

using namespace std;

class MapSection{
	public:
		MapSection(SDL_Renderer *renderer, SDL_Texture *txt, int ypos, SDL_Rect screen);
		MapSection(SDL_Renderer *renderer, SDL_Texture *txt, const char *boundaryFile, int ypos, SDL_Rect screen);
		SDL_Rect *dst();
		SDL_Rect *src();
		SDL_Texture *getTexture();
		void move(int deltay);
		int inScreen();
		void setYpos(int ypos);
		void render();
		SDL_Renderer *renderer;
		int ypos;
		
		vector<SDL_Rect> boundaries;
	private:
		void updateRect();
		SDL_Texture *img;
		
		double scale;
		SDL_Rect src_rect,dst_rect;
		vector<int> boundaryPos;
		SDL_Rect size;
		SDL_Rect screen;
		
		
};

class Bridge: public MapSection{
	public:
		Bridge(SDL_Renderer *renderer, SDL_Texture *txt, int ypos, SDL_Rect screen);
		void destroy();
		void render();
		bool destroyed;
	private:
		
};

class RRMap{
	public:
		RRMap(RRApp * app, SDL_Window *window, SDL_Renderer *renderer);
		void render();
		void update();
		void destroyBridge();
		vector<SDL_Rect> *boundingBoxMap1();
		vector<SDL_Rect> *boundingBoxMap2();
		SDL_Rect boundingBoxBridge();
	private:
		vector<MapSection *> maps;
		int mapindex;
		SDL_Texture *bridgeimg;
		RRApp *app;
		SDL_Window *window;
		SDL_Renderer *renderer;
		int height, width;
		int view_height; 
		SDL_Rect size;
		SDL_Rect rect1,rect2;
		SDL_Rect br;
		MapSection *map1,*map2;
		Bridge *bridge;
		
		SDL_Rect screen;
	
};


#endif

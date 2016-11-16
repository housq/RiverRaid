#ifndef RR_MAP_H
#define RR_MAP_H

#include "SDL2/SDL.h"
#include <memory>
#include <list>
#include <vector>

#include "Asset.h"

class RRApp;

using namespace std;


class RRMap{
	public:
		RRMap(RRApp * app, SDL_Window *window, SDL_Renderer *renderer);
		void render();
		void update();
	private:
		vector<SDL_Texture *> mapimg;
		RRApp *app;
		SDL_Window *window;
		SDL_Renderer *renderer;
		int height, width;
		int view_height; 
		SDL_Rect size;
		SDL_Rect rect1,rect2;
		SDL_Rect br;
		SDL_Texture *img1,*img2, *bridge;
		
		SDL_Rect screen;
		Player *player;
		list<shared_ptr<Projectile>> projectiles;
};

class MapSection{
	public:
		MapSection(SDL_Texture *txt, int ypos);
		SDL_Rect dst();
		SDL_Rect src();
		SDL_Texture *getTexture();
		void move(int deltay);
	private:
		SDL_Texture *img;
		int ypos;
		SDL_Rect size;
};

class Bridge: public MapSection{
	public:
		Bridge(SDL_Texture *txt, int ypos);
		void destroy();
	private:
		bool destroyed = false;
};
#endif

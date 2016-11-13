#ifndef RR_MAP_H
#define RR_MAP_H

#include <memory>
#include <list>
#include "Asset.h"
#include "SDL2/SDL.h"

using namespace std;

class RRMap{
	public:
		RRMap(SDL_Window *window, SDL_Renderer *renderer);
		void render();
		void update();
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture *img1,*img2;
		int height, width;
		SDL_Rect size1,size2;
		SDL_Rect rect1,rect2;
		SDL_Rect screen;
		Player *player;
		list<shared_ptr<Projectile>> projectiles;
};
#endif

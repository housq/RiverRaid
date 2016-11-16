#ifndef RR_APP_H
#define RR_APP_H

#include "SDL2/SDL.h"
#include "RRMap.h"



class RRApp{
	public:
		RRApp(SDL_Window *window, SDL_Renderer *renderer);
		void mainLoop();
		int getSpeed();
		
	private:
		int keyStatus[4] = {0};
		void updateSpeed();
		int speed;
		RRMap *map;
		bool finish;
		SDL_Window *window;
		SDL_Renderer *renderer;
		void updateGame();
		void renderGame();
		void eventHandler(SDL_Event &event);
};

#endif

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "RRApp.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

enum userEvents{UPDATE_EVENT};

Uint32 PushUpdateEvent(Uint32 interval, void *param) {
  SDL_Event event;
  event.type       = SDL_USEREVENT;
  event.user.code  = UPDATE_EVENT;
  event.user.data1 = 0;
  event.user.data2 = 0;
  SDL_PushEvent(&event);
  return interval;
}

int main()
{
	Uint32 width = 800;
	Uint32 height = 600;

    SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window *g_window = SDL_CreateWindow("River Raid"
	                    , SDL_WINDOWPOS_CENTERED
	                    , SDL_WINDOWPOS_CENTERED
	                    , width
	                    , height
	                    , SDL_WINDOW_SHOWN);
	SDL_Renderer * g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	SDL_SetRenderDrawColor(g_renderer, 128, 128, 128, 255);

	RRApp app(g_window, g_renderer);
	int delay = 1000/60; // 1000 milis in a second, divide by 60 - the framerate
  	SDL_AddTimer(delay, PushUpdateEvent, NULL);
	app.mainLoop();
	
	

    SDL_Quit();
    
    return 0;    
}

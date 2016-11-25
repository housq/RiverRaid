#ifndef RR_ASSET_H
#define RR_ASSET_H
#include "RRApp.h"
#include "RRMap.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class RRApp;

class Asset{
	public:
    Asset(RRApp * app, SDL_Window *window, SDL_Renderer *renderer);
    void render();
    void eventHandler(SDL_Event &event);
    void fire(int flag);
    void updateBullet();
    void renderScore();
    SDL_Rect rect1, rect2;
    SDL_Texture  *plane , *bullet;
    int lives;
    int isAlive;
    int score;
    SDL_Texture* ftexture;
    TTF_Font* font ;
    SDL_Color text_color;
	private:
    
    int height, width;
    SDL_Window *window;
    RRApp *app;
    bool fireBullet;
    SDL_Renderer *renderer;
SDL_Surface *s;


};


#endif

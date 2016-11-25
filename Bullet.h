//
//  Bullet.h
//  RiverRaid
//
//  Created by Noor Bafageeh on 11/22/16.
//  Copyright © 2016 Noor Bafageeh. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h
#include "Asset.h"
#include "string"
#include "RRApp.h"
#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
using namespace std ;

class RRApp;
class Asset;


class Bullet{
public:
    Bullet(RRApp * app, SDL_Window *window, SDL_Renderer *renderer, Asset *player);
    void render();
    void fire(int flag);
    void updateBullet();
    SDL_Rect rect2;
    SDL_Texture  *bullet;
    
    
    
private:
    
    int height, width;
    SDL_Window *window;
    RRApp *app;
    bool fireBullet;
    SDL_Renderer *renderer;
    
    
    
};




#endif /* Bullet_h */

//
//  Bullet.cpp
//  RiverRaid
//
//  Created by Noor Bafageeh on 11/22/16.
//  Copyright © 2016 Noor Bafageeh. All rights reserved.
//

#include "Bullet.h"
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

Bullet::Bullet(RRApp * app, SDL_Window *window, SDL_Renderer *renderer, Asset *player)
: app(app), window(window), renderer(renderer){
    SDL_GetWindowSize(window, &width, &height);
    SDL_Surface *loadedImage = IMG_Load("img/bullet.bmp");
    
    if(loadedImage==NULL  ){
        cout<<"Error loading plane img "<< IMG_GetError();
        
    }else{
        bullet = SDL_CreateTextureFromSurface(renderer, loadedImage);
        
        rect2.w = 100;
        rect2.h = 100;
        rect2.x = player->rect1.x + 35;
        rect2.y =  player->rect1.y;
        
        
        
        
        
    }
    
    fireBullet = false;
    
    
}

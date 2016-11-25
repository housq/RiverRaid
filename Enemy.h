//
//  Enemy.h
//  RiverRaid
//
//  Created by Noor Bafageeh on 11/21/16.
//  Copyright © 2016 Noor Bafageeh. All rights reserved.
//

#ifndef Enemy_h
#define Enemy_h

#include "Asset.h"
#include "string"
#include "RRApp.h"
#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

using namespace std ;


class Enemy {
    public:
    Enemy(RRApp * app, SDL_Window *window, SDL_Renderer *renderer);
 
 
    
    SDL_Rect rect1;
    SDL_Texture  *enemy;
    SDL_Renderer *renderer;
    RRApp *app;
    int height, width;
    int isAlive;
    SDL_Window *window;
    
    

    
    
};


#endif /* Enemy_h */

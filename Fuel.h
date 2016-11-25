//
//  Fuel.h
//  RiverRaid
//
//  Created by Noor Bafageeh on 11/21/16.
//  Copyright © 2016 Noor Bafageeh. All rights reserved.
//

#ifndef Fuel_h
#define Fuel_h


#include "Asset.h"
#include "string"
#include "RRApp.h"
#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>

using namespace std ;


class Fuel {
public:
    Fuel(RRApp * app, SDL_Window *window, SDL_Renderer *renderer);
    
    
    SDL_Rect rect1;
    SDL_Texture  *fuel;
    SDL_Renderer *renderer;
    RRApp *app;
    int height, width;
    SDL_Window *window;
    bool fuelEmpty;
    int isVisible;
    
    
    
};
#endif /* Fuel_h */

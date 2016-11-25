//
//  Fuel.cpp
//  RiverRaid
//
//  Created by Noor Bafageeh on 11/21/16.
//  Copyright © 2016 Noor Bafageeh. All rights reserved.
//

#include "Fuel.h"

#include "string"
#include "RRApp.h"
#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std ;




Fuel::Fuel(RRApp * app, SDL_Window *window, SDL_Renderer *renderer): app(app), window(window), renderer(renderer){
    SDL_GetWindowSize(window, &width, &height);
    SDL_Surface *loadedImage = IMG_Load("img/oil3.bmp");
    
    
    if(loadedImage==NULL  ){
        cout<<"Error loading enemy img "<< IMG_GetError();
        
    }else{
        fuel = SDL_CreateTextureFromSurface(renderer, loadedImage);
        rect1.w = 65;
        rect1.h = 65;
        int randx = rand() % (width/2) + 200 ;
        rect1.x = randx;
        rect1.y = 0;
        fuelEmpty = false;
        isVisible =0;
        
    }
    
    
    
    
    
    
}




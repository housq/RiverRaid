#include "Asset.h"
#include "string"
#include "RRApp.h"
#include "RRMap.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>

#include <iostream>
using namespace std ;




Asset::Asset(RRApp * app, SDL_Window *window, SDL_Renderer *renderer)
: app(app), window(window), renderer(renderer){
    SDL_GetWindowSize(window, &width, &height);
    SDL_Surface *loadedImage = IMG_Load("img/plane.bmp");

    if(loadedImage==NULL  ){
        cout<<"Error loading plane img "<< IMG_GetError();

    }else{
        plane = SDL_CreateTextureFromSurface(renderer, loadedImage);
        
        rect1.w = 50;
        rect1.h = 50;
        rect1.x = (width/2)-(rect1.w/2);
        rect1.y =  rect1.x + 20;
        lives = 3;
        isAlive = 0;
        score = 0;
        
       
        

    }
    
    fireBullet = false;
    string fontPath = "img/shangrila_font_7271/shangri-la.ttf";
    font = TTF_OpenFont(fontPath.c_str(), 20);
    
    ftexture = NULL;
     text_color = {0,255,0};
    if (font == NULL) {
        cerr << "Failed the load the font!\n";
    }
   
/*
 SDL_Texture* ftexture;
 TTF_Font* font ;
 SDL_Color text_color;
 
 */
    
    
}




void Asset::render(){
    if (isAlive < 2){
        SDL_RenderCopy(renderer, plane, NULL, &rect1);
        if(isAlive == 1){
            isAlive++;
        }

    }
    if (fireBullet == true){
            SDL_RenderCopy(renderer, bullet, NULL, &rect2);

    }
    


    
}


void Asset::renderScore(){
    
    string socre1 = std::to_string(score);
    
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, socre1.c_str(), text_color);
    ftexture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect textRect ;
    textRect.h = 5;
    textRect.w = 5;
    textRect.x = 370;
    textRect.y = 10;
    
    SDL_RenderCopy(renderer, ftexture, NULL, &textRect);


}


void Asset::updateBullet(){
    if(fireBullet == true){
        rect2.y -= 20;

    }
}


void Asset::fire(int flag){
    if (flag == 1){
        SDL_Surface *loadedImage2 = IMG_Load("img/bullet.bmp");
        bullet = SDL_CreateTextureFromSurface(renderer, loadedImage2);
        rect2.w = 30;
        rect2.h = 30;
        rect2.x = rect1.x + 35;
        rect2.y = rect1.y;
        fireBullet = true;
        
        
    }else{
        flag = 0;
    }
    
}

















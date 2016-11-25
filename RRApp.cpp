#include "RRApp.h"
#include "RRMap.h"
#include "Asset.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Enemy.h"
#include "Fuel.h"
#include "Bullet.h"
#include <SDL2/SDL_ttf.h>


RRApp::RRApp(SDL_Window *window, SDL_Renderer *renderer){
    finish = false;
	this->window = window;
	this->renderer = renderer;
    player1 = new Asset(this, window,renderer);
    map = new RRMap(this, window,renderer);
    SDL_Surface *loadedImgae = IMG_Load("img/6.bmp");
  
    fuleLevelBar = SDL_CreateTextureFromSurface(renderer, loadedImgae);
    fuleRect.h = 20;
    fuleRect.w = 400;
    fuleRect.y = 20;
    fuleRect.x = 20;
	speed = 0;
    lastTime = 0; //for fule
    fuleEmpty = false;
 
    
    
}



int RRApp::getSpeed(){
	return speed;
}




void RRApp::updateFuleBar(){
    int currentTime = SDL_GetTicks();
    if(currentTime > lastTime + 1000){
        if (fuleRect.w >= 50){
            fuleRect.w -= 50;
            lastTime = currentTime;
        }else{
            fuleEmpty = true;
        }
        
    }
    
}




void RRApp::checkFule(){
    if (fuleEmpty == true){
        SDL_Surface *bomb = IMG_Load("img/bomb.bmp");
        player1->plane = SDL_CreateTextureFromSurface(renderer, bomb);

    }
}




void RRApp::renderFuleBar(){
    SDL_RenderCopy(renderer, fuleLevelBar, NULL, &fuleRect);

}



void RRApp::checkFuleColiison(int i){
    SDL_Rect c;
    if (SDL_IntersectRect(&player1->rect2 , &fuleVec[i]->rect1, &c) == true){
        fuleRect.w += 20;
        fuleVec[i]->isVisible = 1;
        player1->score+=10;
        
    }
    
}




void RRApp::updatePlayerPosition(int flag){
    
    if (flag == 1){
        player1->rect1.x -= 50;
    }else if (flag ==2){
        player1->rect1.x += 50;
        
        
    }else{
        player1->rect1.x += 0;
        
    }
    
    
}



void RRApp::generateEnemies(){

        for (int i =0; i<3 ;i++){
            Enemy *enymyPlane = new Enemy (this, window,renderer);
            enemyVec.push_back(enymyPlane);
        }
    
    updateEnemyPoistion();
        
}




void RRApp::checkPlayerFuleCollison(int i){
    SDL_Rect c;
    if (SDL_IntersectRect(&player1->rect1 , &fuleVec[i]->rect1, &c) == true &&fuleVec[i]->isVisible ==0 ){
        player1->lives --;
        if(player1->lives == 0){
            SDL_Surface *bomb = IMG_Load("img/bomb.bmp");
            player1->plane = SDL_CreateTextureFromSurface(renderer, bomb);
            player1->isAlive = 1;
        }
        
    }

    
    
    
}


void RRApp::checkPlayerEnemyCollison(int i){
    SDL_Rect c;
    if (SDL_IntersectRect(&player1->rect1 , &enemyVec[i]->rect1, &c) == true &&enemyVec[i]->isAlive ==0 ){
        cout<<"LIVES = "<<player1->lives<<endl;
        player1->lives --;
        if(player1->lives == 0){
            SDL_Surface *bomb = IMG_Load("img/bomb.bmp");
            player1->plane = SDL_CreateTextureFromSurface(renderer, bomb);
            player1->isAlive = 1;
        }

  }
}


void RRApp::checkBulletEnemyCollison(int i ){
    SDL_Rect c;
    if (SDL_IntersectRect(&player1->rect2 , &enemyVec[i]->rect1, &c) == true){
        SDL_Surface *bomb = IMG_Load("img/bomb.bmp");
        enemyVec[i]->enemy = SDL_CreateTextureFromSurface(renderer, bomb);
        enemyVec[i]->isAlive = 1;
        player1->score+=10;

    }
    
}


void RRApp::updateEnemyPoistion(){
    for (int i =0; i<3 ;i++){
        enemyVec[i]->rect1.y += 4;
        checkPlayerEnemyCollison(i);
        checkBulletEnemyCollison(i);
        
    }
   
}



void RRApp::renderEnemy(){
    for (int i =0; i<3; i++) {
        if(enemyVec[i]->isAlive < 2){
            SDL_RenderCopy(renderer, enemyVec[i]->enemy, NULL, &enemyVec[i]->rect1);
            if(enemyVec[i]->isAlive == 1){
                enemyVec[i]->isAlive++;
            }

        }

    }
    
    
}




void RRApp::clearEnemies (){
     if (enemyVec[0]->rect1.y > 600  && enemyVec[1]->rect1.y > 600 && enemyVec[2]->rect1.y > 600){
         enemyVec.clear();
     }
    
}



void RRApp::generateFule(){
    
    for (int i =0; i<1 ;i++){
        Fuel *fuelStation = new Fuel (this, window,renderer);
        fuleVec.push_back(fuelStation);
    }
    
    updateFuelPoistion();
}


void  RRApp::updateFuelPoistion(){
    for (int i =0; i<1 ;i++){
        fuleVec[i]->rect1.y += 4;
        checkFuleColiison(i);
        checkPlayerFuleCollison(i);
        
    }
    
}


void RRApp::renderFuel(){
    
    for (int i =0; i<1; i++) {
        if(fuleVec[i]->isVisible < 2){
            SDL_RenderCopy(renderer, fuleVec[i]->fuel, NULL, &fuleVec[i]->rect1);
            if(fuleVec[i]->isVisible  == 1){
                fuleVec[i]->isVisible ++;
            }
        }

        
    }
}


void RRApp::clearFuel(){
    if (fuleVec[0]->rect1.y > 1200   ){
        fuleVec.clear();
    }
    
}




void RRApp::updateSpeed(){
	if(keyStatus[2] == 0)
		if(keyStatus[3] == 0)
			speed = 0;
		else
			speed = -1;
	else
		if(keyStatus[3]==0)
			speed = 1;
		else
			speed = 0;
}






void RRApp::mainLoop(){
	SDL_Event event;
    start = SDL_GetTicks();
    running = true;

	while (SDL_WaitEvent(&event) && !finish) {
		eventHandler(event);
	}
    running = false;

     start = 0;
}

void RRApp::updateGame(){
	map->update();
    player1->updateBullet();
     generateEnemies();
    generateFule();
    updateFuleBar();
    checkFule();
    checkBulletMapCollision();
    checkPlayerMapCollision();
}

void RRApp::renderGame(){
	SDL_RenderClear(renderer);
	map->render();
    player1->render();
    renderEnemy();
    renderFuel();
    renderFuleBar();
    player1->renderScore();
    SDL_RenderPresent(renderer);
    clearEnemies();
    clearFuel();
    //cout<<"SCORE = " << player1->score <<endl;
    
}


void RRApp::eventHandler(SDL_Event &event){
	switch (event.type)	{
		case SDL_QUIT:
			finish = true;
			break;
		case SDL_USEREVENT:
    		updateGame();
    		renderGame();
    		break;
    	
        case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			    case SDLK_LEFT:
			      keyStatus[0] = 1;
                    updatePlayerPosition(1);

			      break;
			    case SDLK_RIGHT:
			      keyStatus[1] = 1;
                    updatePlayerPosition(2);

			      break;
			    case SDLK_UP:
			      keyStatus[2] = 1;
			      break;
			    case SDLK_DOWN:
			      keyStatus[3] = 1;
			      break;
                case SDLK_SPACE:
                    keyStatus[4] = 1;
                    player1->fire(1);

                    break;
			}
			updateSpeed();

			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			    case SDLK_LEFT:
			      keyStatus[0] = 0;
                    updatePlayerPosition(0);
			      break;
			    case SDLK_RIGHT:
			      keyStatus[1] = 0;
                    updatePlayerPosition(0);


			      break;
			    case SDLK_UP:
			      keyStatus[2] = 0;
			      break;
			    case SDLK_DOWN:
			      keyStatus[3] = 0;
			      break;
                case SDLK_SPACE:
                    keyStatus[4] = 0;
                    player1->fire(0);
                    
                    break;
			}
			updateSpeed();


			break;
         
		default:
			break;
	}
}


void RRApp::checkBulletMapCollision(){
	SDL_Rect c;

	SDL_Rect bridge = map->boundingBoxBridge();
	if(bridge.h != -1 &&SDL_IntersectRect(&player1->rect2 , &bridge, &c) == true) {
		map->destroyBridge();
	}
}

void RRApp::checkPlayerMapCollision(){
	SDL_Rect c;
	vector<SDL_Rect> *map1b, *map2b;
	map1b = map->boundingBoxMap1();
	map2b = map->boundingBoxMap2();
	SDL_Rect bridge = map->boundingBoxBridge();
	if(bridge.h != -1 &&SDL_IntersectRect(&player1->rect1 , &bridge, &c) == true) {
		player1->lives --;
	}
	if(map1b) for(int i=0;i<map1b->size();i++){
		if(SDL_IntersectRect(&(*map1b)[i] , &player1->rect1, &c) == true) {
			player1->lives --;
		}
	}
	if(map2b) for(int i=0;i<map2b->size();i++){
		if(SDL_IntersectRect(&(*map2b)[i] , &player1->rect1, &c) == true) {
			player1->lives --;
		}
	}
	
}

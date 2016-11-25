#ifndef RR_APP_H
#define RR_APP_H
#include "Asset.h"
#include "SDL2/SDL.h"
#include "RRMap.h"
#include "Fuel.h"
#include <vector>
#include "Bullet.h"


class Fuel;
class Asset;
class Bullet;
class Enemy;

class RRApp{
	public:
		RRApp(SDL_Window *window, SDL_Renderer *renderer);
		void mainLoop();
		int getSpeed();
        void generateEnemies();
        void updateEnemyPoistion();
        void renderEnemy();
        void clearEnemies();
    void updatePlayerPosition(int flag);
        void generateFule();
        void updateFuelPoistion();
        void renderFuel();
        void clearFuel();
    void renderBullet();
   void fireBullet(int flag);
    void checkPlayerEnemyCollison(int i);
    void checkBulletEnemyCollison(int i);
    void checkPlayerFuleCollison(int i);
    void checkBulletMapCollision();
    void checkPlayerMapCollision();
    void renderFuleBar();
    void updateFuleBar();
    void checkFule();
    void checkFuleColiison(int i);
    void buildFuleVec();
    int lastTime , lastTime2;
    SDL_Texture  *fuleLevelBar;
    SDL_Rect fuleRect;
    int maxFuleNumber;
    int fuleI;
	private:
		int keyStatus[5] = {0};
		void updateSpeed();
    int maxBullet;
		int speed , xspeed;
		RRMap *map;
        Asset *player1;
      Uint32 start = 0;
    bool running;
    bool fuleEmpty;
       vector<Enemy*> enemyVec;
       vector<Fuel*> fuleVec;
       vector<Bullet*> bulletVec;
    
		bool finish , f , fired;
		SDL_Window *window;
		SDL_Renderer *renderer;
		void updateGame();
		void renderGame();
		void eventHandler(SDL_Event &event);
};

#endif

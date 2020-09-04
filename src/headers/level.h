#ifndef Level_h
#define Level_h
#include "graphics.h"
#include "player.h"
#include "enemy.h"
#include "audio.h"
#include "music.h"

#include <string>
#include <iostream>
#include <vector>
using std::vector;

class Graphics;
class Player;
class Enemy;

class Level {
    public:
        Level();
        Level(Graphics &graphics, int levelNum, vector<vector<int>> enemyList);

        /*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        */
        void handleEvents();
        void update(Player &_player, Graphics &_graphics);
        void draw(Graphics &graphics);

        int getLevelNumber() {return this->number;}

        bool getClear() { return this->clear; }

        Music levelBGMusic;



    private:

        int number;
        int enemiesPerScreen;
        bool clear;
        bool bossPhase = false;
        vector<SDL_Texture*> _backgroundTextures;
        vector<Enemy*> _enemies;
        vector<Enemy*> _enemiesBacklog;
        vector<Enemy*> _bosses;
        Audio _enemyKOAudio;
        Audio _levelClearAudio;
        Music _bossMusic;


};

#endif
#ifndef Level_h
#define Level_h
#include "graphics.h"
#include "player.h"
#include "enemy.h"

#include <vector>
using std::vector;

class Graphics;
class Player;
class Enemy;

class Level {
    public:
        Level();
        Level(Graphics &graphics, int levelNum);

        /*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        */
        void handleEvents();
        void update(Player &_player);
        void draw(Graphics &graphics);


    private:
        int number;
        SDL_Texture* _backgroundText;
        vector<Enemy*> _enemies;

};

#endif
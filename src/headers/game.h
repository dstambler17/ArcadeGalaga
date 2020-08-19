#ifndef Game_h
#define Game_h
#include "graphics.h"
#include "player.h"
#include "level.h"
#include "textmanager.h"


class Game {
    public:
        Game();
        ~Game();

        /*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        */
        void handleEvents();
        void update();
        void render();
        //void clean();

        bool running() {return isRunning;}

    private:
        
        bool isRunning;
        Graphics _graphics;
        Player _player;
        Level _level;
        TextManager _textmanager;
        SDL_Texture* _scoreTex;
};

#endif
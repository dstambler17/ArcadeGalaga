#ifndef Game_h
#define Game_h
#include "graphics.h"
#include "player.h"

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
};

#endif
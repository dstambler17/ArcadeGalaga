#ifndef Game_h
#define Game_h
#include "graphics.h"
#include "player.h"
#include "level.h"
#include "textmanager.h"
#include "audio.h"
#include <vector>


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
        vector<Level*> _levels;
        TextManager _textmanager;
        SDL_Texture* _scoreTex;
        Audio _audio;
};

#endif
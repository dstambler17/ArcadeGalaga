#ifndef Game_h
#define Game_h
#include "graphics.h"
#include "player.h"
#include "level.h"
#include "textmanager.h"
#include "endscreen.h"
#include "audio.h"
#include <vector>


class Game {
    public:
        Game();
        ~Game();

        /*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        */
        void handleEvents();
        void handleGameEndEvents();
        void update();
        void render();
        //void clean();

        bool running() {return isRunning;}
        bool isGameOver;
        bool isGameWin;

    private:
        
        bool isRunning;
        int gameScore = 0;
        Graphics _graphics;
        Player _player;
        EndScreen _gameOverScreen = EndScreen(_graphics, false);
        EndScreen _gameWinScreen = EndScreen(_graphics, true);
        vector<Level*> _levels;
        TextManager _scoreTextManager;
        TextManager _levelTextManager;
        SDL_Texture* _scoreTex;
        Audio _audio;
};

#endif
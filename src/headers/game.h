#ifndef Game_h
#define Game_h
#include "graphics.h"
#include "player.h"
#include "level.h"
#include "textmanager.h"
#include "endscreen.h"
#include "titlescreen.h"
#include "audio.h"
#include <vector>

class Game {
    public:
        Game();
        ~Game();

        /*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        */
        void handleEvents();
        void handleGameStartEvents();
        void handleGameEndEvents();
        void update();
        void render();
        //void clean();

        bool running() {return isRunning;}
        bool isGameOver;
        bool isGameWin;
        bool isGameStart = true;

    private:
        
        bool isRunning;
        int gameScore = 0;
        Graphics _graphics;
        Player _player;
        EndScreen _gameOverScreen = EndScreen(_graphics, false);
        EndScreen _gameWinScreen = EndScreen(_graphics, true);
        TitleScreen titleScreen = TitleScreen(_graphics);
        vector<Level*> _levels;
        TextManager _scoreTextManager;
        TextManager _levelTextManager;
        SDL_Texture* _scoreTex;
        Audio _audio;
        Audio _victoryAudio;
        Audio _gameOverAudio;
};

#endif
#include <iostream>
#include "headers/game.h"
#include "headers/music.h"
using namespace std;

Game *game = nullptr;
int main(){
    
    //Limit FrameRate
    const int FPS = 60;
    const int FrameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    Music("content/music/caveStory.ogg").play();
    while (game->running()){
        frameStart = SDL_GetTicks();

        if (game->isGameOver || game->isGameWin){
            game->handleGameEndEvents();
        
        } else if (game->isGameStart) {
            game->handleGameStartEvents();
        } else {
            game->handleEvents();
            game->update();
        }
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (FrameDelay > frameTime){
            SDL_Delay(FrameDelay - frameTime);
        }

    }
    return 0;
}

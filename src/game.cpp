#include <SDL2/SDL.h>
#include <iostream>
#include "headers/game.h"
#include "headers/graphics.h"
#include "headers/player.h"
#include <string>
#include <iostream>

Game::Game(){
    //SDL_Init(SDL_INIT_EVERYTHING);
    isRunning = true;
    this->_player = Player(_graphics);
}

Game::~Game()
{}

/*void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "SDL_Initialized";
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        isRunning = true;
    } else{
        isRunning = false;
    }
}*/

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_LEFT) { // move left
                std::cout << "left" << std::endl;
                this->_player.moveLeft();
            }
            if(event.key.keysym.sym == SDLK_RIGHT) { // move right
                std::cout << "right" << std::endl;
                this->_player.moveRight();
            }

            if(event.key.keysym.sym == SDLK_UP) { // move up
                std::cout << "up" << std::endl;
                this->_player.moveUp();
            }
            if(event.key.keysym.sym == SDLK_DOWN) { // move down
                std::cout << "down" << std::endl;
                this-> _player.moveDown();
            }
            if(event.key.keysym.sym == SDLK_s) { // move down
                std::cout << "pew pew" << std::endl;
                this-> _player.fireLazer(_graphics);
            }
            
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}




void Game::update(){
    _player.update();
}

void Game::render(){
    _graphics.clear();
    _player.draw(_graphics);
    _graphics.flip();
}

/*void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}*/
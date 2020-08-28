#include <SDL2/SDL.h>
#include <iostream>
#include "headers/game.h"
#include "headers/graphics.h"
#include "headers/player.h"
#include "headers/level.h"
#include "headers/textmanager.h"
#include "headers/audio.h"

#include <string>
#include <iostream>
#include <vector>


Game::Game(){
    isRunning = true;
    this->_player = Player(_graphics);
    //Each vector will have 4 variables: enemy number, x_start, y_start, true/false
    /*
    Enemy int reference:
        1. EyeBot
        2. UFO
        3. EnemyShip
    */
    vector<vector<int>> levelOneInfo{ {1, 150, 200, 1}, {2, 325, 250, 0},
                {2, 600, 375, 1}, {3, 420, 50, 1}}; 
    this->_level = Level(_graphics, 1, levelOneInfo);
    this->_textmanager = TextManager(_graphics);
    std::cout << "CALL TESTER" <<std::endl;
    
    this->_audio.load("content/audio/lazer.wav");
}

Game::~Game()
{}


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
            if(event.key.keysym.sym == SDLK_s) { // fire lazer
                std::cout << "pew pew" << std::endl;
                this-> _player.fireLazer(_graphics);
                //this->_audio.play();
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
    _level.update(_player, _graphics);
    if (_level.getClear()){
        std::cout << "WINNER" <<std::endl;
        isRunning = false;
    }
    if (_player.getHealth() <= 0){
        std::cout << "HEALTH TO NULL" <<std::endl;
        isRunning = false;
    }

    if (_textmanager.getScore() < _player.getPlayerScore()){
        _textmanager.updateScoreTex(_graphics, _player.getPlayerScore());
    }
}

void Game::render(){
    _graphics.clear();
    _level.draw(_graphics);
    _player.draw(_graphics);
    _textmanager.draw(_graphics);
    _graphics.flip();
}

/*void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}*/
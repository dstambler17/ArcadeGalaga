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
    isGameOver = false;
    isGameWin = false;
    this->_player = Player(_graphics);
    //Each vector will have 4 variables: enemy number, x_start, y_start, true/false, is boss true/false
    /*
    Enemy int reference:
        1. EyeBot
        2. UFO
        3. EnemyShip
        4. BossShip
    */
    vector<vector<int>> levelOneInfo{{3, 420, 50, 1, 0}, {1, 150, 200, 1, 0}, {2, 325, 250, 0, 0},
                {2, 600, 375, 1, 0}, {1, 200, 100, 1, 0}, {1, 300, 300, 0, 0}, {4, 300, 30, 1, 1}};
    vector<vector<int>> levelTwoInfo{{3, 420, 50, 1, 0}, {2, 150, 200, 1, 0}, {2, 325, 250, 0, 0},
                {2, 600, 375, 1, 0}, {1, 200, 100, 1, 0}, {1, 300, 300, 0, 0}, {2, 300, 30, 1, 1}};
    this->_levels.push_back(new Level(_graphics, 1, levelOneInfo));  
    this->_levels.push_back(new Level(_graphics, 2, levelTwoInfo));  
    this->_scoreTextManager = TextManager(_graphics, "Score: 0", "content/fonts/OpenSans.ttf");
    this->_levelTextManager = TextManager(_graphics, "Level: 1", "content/fonts/OpenSans.ttf");

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

/*Handles user input at end of game*/
void Game::handleGameEndEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_q) { // exit game
                isRunning = false;
            }
            if(event.key.keysym.sym == SDLK_s) { // restart
                isGameOver = false;
                isGameWin = false;
                this->_levels.clear();
                vector<vector<int>> levelOneInfo{{3, 420, 50, 1, 0}, {1, 150, 200, 1, 0}, {2, 325, 250, 0, 0},
                {2, 600, 375, 1, 0}, {1, 200, 100, 1, 0}, {1, 300, 300, 0, 0}, {4, 300, 30, 1, 1}};
                vector<vector<int>> levelTwoInfo{{3, 420, 50, 1, 0}, {2, 150, 200, 1, 0}, {2, 325, 250, 0, 0},
                            {2, 600, 375, 1, 0}, {1, 200, 100, 1, 0}, {1, 300, 300, 0, 0}, {2, 300, 30, 1, 1}};
                this->_levels.push_back(new Level(_graphics, 1, levelOneInfo));  
                this->_levels.push_back(new Level(_graphics, 2, levelTwoInfo));
                _player.setPlayerScore(0);
                _player.setPlayerHealth(3);
                _player.clearLazers();
                this->gameScore = 0;
                this->_scoreTextManager = TextManager(_graphics, "Score: 0", "content/fonts/OpenSans.ttf");
                this->_levelTextManager = TextManager(_graphics, "Level: 1", "content/fonts/OpenSans.ttf");  
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
    if (isGameOver || isGameWin){
        return;
    }
    _player.update();
    Level* curLevel = this->_levels.at(0);
    curLevel->update(_player, _graphics);
    //EITHER LOAD NEXT LEVEL OR CLEAR
    if (curLevel->getClear()){
        std::cout << "WINNER OF LEVEL" <<std::endl;
        this->_levels.erase(this->_levels.begin());
        if (this->_levels.size() == 0){
            std::cout << "WINNER OF GAME" <<std::endl;
            isGameWin = true;
        } else {
            Level* nextLevel = this->_levels.at(0);
            std::string newLevelText = "Level: " + std::to_string(nextLevel->getLevelNumber());
            _levelTextManager.updateTex(_graphics, newLevelText);
        }
        
    }
    if (_player.getHealth() <= 0){
        std::cout << "HEALTH TO NULL" <<std::endl;
        isGameOver = true;
    }

    if (this->gameScore < _player.getPlayerScore()){
        this->gameScore = _player.getPlayerScore();
        std::string newScoreText = "Score: " + std::to_string(_player.getPlayerScore());
        _scoreTextManager.updateTex(_graphics, newScoreText);
    }
}

void Game::render(){
    _graphics.clear();
        if (isGameOver){
            _gameOverScreen.draw(_graphics);
        } else if (isGameWin){
            _gameWinScreen.draw(_graphics);
        } else{
            if (_levels.size() > 0){
                _levels.at(0)->draw(_graphics);
            }
            _player.draw(_graphics);
            SDL_Rect levelText = {720,20,80,40};
            SDL_Rect scoreText = {720, -10, 80, 40};
            _levelTextManager.draw(_graphics, &levelText);
            _scoreTextManager.draw(_graphics, &scoreText);
        }
        
    _graphics.flip();
}

/*void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}*/
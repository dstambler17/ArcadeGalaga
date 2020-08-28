#include "headers/level.h"
#include "headers/graphics.h"
#include "headers/enemy.h"

#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::__fs::filesystem;

Level::Level() {}
Level::Level(Graphics &graphics, int levelNum, vector<vector<int>> enemyList) {

   
    fs::path pathToShow("content/backgrounds/");
    for (const auto& entry : fs::directory_iterator(pathToShow)) {
        auto file = entry.path().filename();
        std::string pathString = "content/backgrounds/" + file.u8string();
        SDL_Surface* bgSurface = graphics.loadImage(pathString);
        std::cout << file.c_str() << std::endl;
        if (!bgSurface){
            std::cout << "ERROR" << std::endl;
        } else {
            this->_backgroundTextures.push_back(SDL_CreateTextureFromSurface(graphics.getRenderer(), bgSurface));
        }
    }
        


    this->number = levelNum;
    this->clear = false;
    for (vector<int> enemyData : enemyList){
        int x_val = enemyData[1];
        int y_val = enemyData[2];
        bool side = enemyData[3];
        switch(enemyData[0]) {
            case 1:
                this->_enemies.push_back(new EyeBot(graphics, x_val, y_val, side));
                 break;
            case 2:
                this->_enemies.push_back(new UFO(graphics, x_val, y_val, side));
                break;
            case 3:
                this->_enemies.push_back(new EnemyShip(graphics, x_val, y_val, side));
                break;
            default :
                break;
        }
    }
    /*this->_enemies.push_back(new EyeBot(graphics, 200, 100, true));
    this->_enemies.push_back(new EyeBot(graphics, 150, 200, true));
    this->_enemies.push_back(new EyeBot(graphics, 300, 300, false));
    this->_enemies.push_back(new UFO(graphics, 325, 250, false));
    this->_enemies.push_back(new UFO(graphics, 600, 375, true));
    this->_enemies.push_back(new EnemyShip(graphics, 420, 50, true));*/

    
}

void Level::update(Player &_player, Graphics &_graphics) {
     vector<int> deleteIdx;
    int i = 0;
    for (int c = 0; c < this->_enemies.size(); c++){
        if (_enemies.at(c)->getCanFireLazers()){
            this->_enemies.at(c)->update(_graphics);
        } else {
            this->_enemies.at(c)->update();
        }
        Enemy* enemy = this->_enemies.at(c);
        if (enemy->getBoundingBox().collidesWith(_player.getBoundingBox())) {
		    _player.handleEnemyCollisions();
	    }
        _player.handleLazerCollisions(enemy);
        enemy->handleLazerCollisions(&_player);
        if (enemy->getHealth() <= 0){
            deleteIdx.push_back(i);
            _player.updateScore(enemy->getPoints());
        }
        i += 1;
    }
    //Remove Enemies with health above zero
    for (int idx : deleteIdx){
       this->_enemies.erase(this->_enemies.begin() + idx);
    }
    deleteIdx.clear();

    if (_enemies.size() == 0){
        this->clear = true;
    }

}

void Level::draw(Graphics &graphics) {
    //Draw BG First
    SDL_Rect bgTile = {0,0,100, 100};
    int tile_num = 0;
    for (int x = 0; x < 8; x++){
        bgTile.x = x * 100;
        for (int y = 0; y < 6; y++){
            bgTile.y = y * 100;
            graphics.blitSurface(this->_backgroundTextures.at(tile_num), NULL, &bgTile);
            tile_num = (tile_num + 1) % this->_backgroundTextures.size();
           
        }
    }
    for (Enemy* enemy : _enemies){
        enemy->draw(graphics);
    }
}

#include "headers/level.h"
#include "headers/graphics.h"
#include "headers/enemy.h"

#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::__fs::filesystem;

Level::Level() {}
Level::Level(Graphics &graphics, int levelNum) {

   
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
    this->_enemies.push_back(new EyeBot(graphics, 200, 100, true));
    this->_enemies.push_back(new EyeBot(graphics, 150, 200, true));
    this->_enemies.push_back(new EyeBot(graphics, 300, 300, false));
    this->_enemies.push_back(new UFO(graphics, 325, 250, false));
    this->_enemies.push_back(new UFO(graphics, 600, 375, true));
    this->_enemies.push_back(new EnemyShip(graphics, 420, 50, true));

    
}

void Level::update(Player &_player) {
     vector<int> deleteIdx;
    int i = 0;
    for (int c = 0; c < this->_enemies.size(); c++){
        this->_enemies.at(c)->update();
        Enemy* enemy = this->_enemies.at(c);
        if (enemy->getBoundingBox().collidesWith(_player.getBoundingBox())) {
		    _player.handleEnemyCollisions(enemy);
	    }
        _player.handleLazerCollisions(enemy);
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

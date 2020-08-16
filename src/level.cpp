#include "headers/level.h"
#include "headers/graphics.h"
#include "headers/enemy.h"

#include <string>
#include <iostream>
#include <vector>
using std::vector;

Level::Level() {}
Level::Level(Graphics &graphics, int levelNum) {
    this->number = levelNum;
    this->_enemies.push_back(new EyeBot(graphics, 200, 100));
    this->_enemies.push_back(new EyeBot(graphics, 150, 200));
    this->_enemies.push_back(new EyeBot(graphics, 300, 300));
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
        }
        i += 1;
    }
    //Remove Enemies with health above zero
    for (int idx : deleteIdx){
       this->_enemies.erase(this->_enemies.begin() + idx);
    }
    deleteIdx.clear();
}

void Level::draw(Graphics &graphics) {
    for (Enemy* enemy : _enemies){
        enemy->draw(graphics);
    }
}

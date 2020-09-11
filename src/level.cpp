#include "headers/level.h"
#include "headers/graphics.h"
#include "headers/enemy.h"
#include "headers/audio.h"
#include "headers/music.h"


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
        if (!bgSurface){
            std::cout << "ERROR WITH BG SURFACE" << std::endl;
        } else {
            this->_backgroundTextures.push_back(SDL_CreateTextureFromSurface(graphics.getRenderer(), bgSurface));
        }
    }
        
    this->_enemyKOAudio = Audio("content/audio/explosion.wav", 2);
    this->_levelClearAudio = Audio("content/audio/levelClear.wav", 3);
    this->levelBGMusic = Music("content/music/caveStoryLevel.ogg");
    this->_bossMusic = Music("content/music/caveStoryBoss.ogg");

    this->enemiesPerScreen = 5; //NOTE: SHOULD BE A CONSTRUCTOR PARAM
    this->number = levelNum;
    this->clear = false;
    for (vector<int> enemyData : enemyList){
        int x_val = enemyData[1];
        int y_val = enemyData[2];
        bool side = enemyData[3];
        bool isBoss = enemyData[4];
        vector<Enemy*> *pushList = (isBoss) ? &this->_bosses: &this->_enemiesBacklog; 
        switch(enemyData[0]) {
            case 1:
                pushList->push_back(new EyeBot(graphics, x_val, y_val, side));
                 break;
            case 2:
                pushList->push_back(new UFO(graphics, x_val, y_val, side));
                break;
            case 3:
                pushList->push_back(new EnemyShip(graphics, x_val, y_val, side));
                break;
            case 4:
                pushList->push_back(new BossShip(graphics, x_val, y_val, side));
                break;
            default :
                break;
        }
    }
}


void Level::update(Player &_player, Graphics &_graphics) {

    /* Pull From backlog if less than ENEMIES PER SCREEN in enemies */
    while (this->_enemies.size() < this->enemiesPerScreen && this->_enemiesBacklog.size() > 0){
        this->_enemies.push_back(this->_enemiesBacklog.back());
        this->_enemiesBacklog.pop_back();
    }

    while (this->_enemies.size() == 0 && this->_enemiesBacklog.size() == 0 && this->_bosses.size() > 0){
        if (!this->bossPhase){
            this->_bossMusic.play();
            this->bossPhase = true;
        }
        this->_enemies.push_back(this->_bosses.back());
        this->_bosses.pop_back();
    }

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
        enemy->handleLazerCollisions(&_player);
        _player.handleLazerCollisions(enemy);
        if (enemy->getHealth() <= 0){
            this->_enemyKOAudio.play();
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

    if (_enemies.size() == 0 && this->_enemiesBacklog.size() == 0 && this->_bosses.size() == 0){
        this->_enemyKOAudio.pause();
        this->_levelClearAudio.play();
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

#include "headers/enemy.h"
#include "headers/lazer.h"

#include <string>
#include <iostream>
#include <vector>
using std::vector;


namespace enemy_constants {
    const int SCREEN_WIDTH = 750;
    const int SCREEN_HIGHT = 550;
	const int ABOVE_SCREEN_SPAWN = -50;
}

//Base enemy class
Enemy::Enemy() {}

Enemy::Enemy(Graphics &graphics, std::string filePath, int spawnX, int spawnY,
			int width, int height, int startY):
				Sprite(graphics, filePath, width, height, spawnX, spawnY)
{
	this->inStartingPos = false;
	this->trueStart = startY;
}

void Enemy::fireLazer(Graphics &graphics, int xPlus, int yPlus){
    this->_lazers.push_back(Lazer(graphics, false, this->_x + xPlus, this->_y + yPlus, "content/sprites/lazerEnemy.png"));
}

void Enemy::update(Graphics & graphics){}
void Enemy::update() {
	if (!this->inStartingPos){
		this->moveToStart();
	} else if (this->_shouldMoveSide) {
		if (this->_positiveDir){
			this->_x += this->speed;
		} else {
			this->_x -= this->speed;
		}
		this->_positiveDir = (this->_x < 700 && this->_x > 10) ? this->_positiveDir: !this->_positiveDir;
	} else {
		if (this->_positiveDir){
			this->_y += this->speed;
		} else {
			this->_y -= this->speed;
		}
		this->_positiveDir = (this->_y < 540 && this->_y > 10) ? this->_positiveDir: !this->_positiveDir;
	}
	vector<int> deleteIdx;
    if (this->_lazers.size() > 0){
        int i = 0;
        for (Lazer &lazer : this->_lazers){
            if (lazer.getY() <= enemy_constants::SCREEN_HIGHT + 20){
                lazer.travel();
                lazer.update();
            } else{
                deleteIdx.push_back(i);
                //std::cout << this->_lazers.size() << std::endl;
            }
            i += 1;
        }
    }
    //Clear All Lazers

    //Remove Lazers that are no longer used
    for (int idx : deleteIdx){
       this->_lazers.erase(this->_lazers.begin() + idx);
    }
    deleteIdx.clear();
	Sprite::update();
}

void Enemy::handleLazerCollisions(Player* player) {
    //Collect Collided with enemies
    vector<int> deleteIdx;
    if (this->_lazers.size() > 0){
        int i = 0;
        for (Lazer &lazer : this->_lazers){
            if (lazer.getBoundingBox().collidesWith(player->getBoundingBox())){
                lazer.collideWithPlayer(player);
                deleteIdx.push_back(i);
            }
            i += 1;
        }
    }
    //Remove Lazers that are no longer used
    for (int idx : deleteIdx){
       this->_lazers.erase(this->_lazers.begin() + idx);
    }
    deleteIdx.clear();
}

void Enemy::loseHealth(int damage){
	this->health -= damage;
}

void Enemy::moveToStart(){
	this->_y += this->speed;
	if (this->_y >= this->trueStart){
		this->inStartingPos = true;
	}
}

void Enemy::draw(Graphics &graphics) {
	if (this->_lazers.size() > 0){
        for (Lazer &lazer : this->_lazers){
            lazer.draw(graphics);
        }   
    }
	Sprite::draw(graphics, this->_x, this->_y);
}


//eyebot class
EyeBot::EyeBot() {}

EyeBot::EyeBot(Graphics &graphics, int spawnX, int spawnY, bool shouldMoveSide):
		Enemy(graphics, "content/sprites/eyebot.png", spawnX, enemy_constants::ABOVE_SCREEN_SPAWN, 32, 32, spawnY),
		_startingX(spawnX),
		_startingY(spawnY)
{
	this->health = 1;
	this->points = 10;
	this->_shouldMoveSide = shouldMoveSide;
	this->speed = 2;
}

void EyeBot::update() {
	Enemy::update();
}


void EyeBot::draw(Graphics &graphics) {
	Enemy::draw(graphics);
}


//spaceship class
UFO::UFO() {}

UFO::UFO(Graphics &graphics, int spawnX, int spawnY, bool shouldMoveSide):
		Enemy(graphics, "content/sprites/alien.png", spawnX, enemy_constants::ABOVE_SCREEN_SPAWN, 40, 40, spawnY),
		_startingX(spawnX),
		_startingY(spawnY)
{
	this->health = 3;
	this->points = 50;
	this->_shouldMoveSide = shouldMoveSide;
	this->speed = 5;
}

void UFO::update() {
	Enemy::update();
}


void UFO::draw(Graphics &graphics) {
	Enemy::draw(graphics);
}


//Enemy Ship Class
EnemyShip::EnemyShip() {}

EnemyShip::EnemyShip(Graphics &graphics, int spawnX, int spawnY, bool shouldMoveSide):
		Enemy(graphics, "content/sprites/enemyShip.png", spawnX, enemy_constants::ABOVE_SCREEN_SPAWN, 40, 40, spawnY),
		_startingX(spawnX),
		_startingY(spawnY)
{
	this->health = 5;
	this->points = 100;
	this->_shouldMoveSide = shouldMoveSide;
	this->speed = 1;
	this->canFireLazers = true;
}



void EnemyShip::update(Graphics &graphics) {
	if (((int) this->getX()) % 50 == 0 && this->getInStartPos()){
		//EnemyShip* e = dynamic_cast<EnemyShip*>(enemy);
		this->fireLazer(graphics, 15, 5);
		//e->handleLazerCollisions(_player);
    }
	Enemy::update();
}


void EnemyShip::draw(Graphics &graphics) {
	Enemy::draw(graphics);
}


//Boss Ship Class
BossShip::BossShip() {}

BossShip::BossShip(Graphics &graphics, int spawnX, int spawnY, bool shouldMoveSide):
		Enemy(graphics, "content/sprites/boss.png", spawnX, enemy_constants::ABOVE_SCREEN_SPAWN, 250, 250, spawnY),
		_startingX(spawnX),
		_startingY(spawnY)
{
	this->health = 20;
	this->points = 2000;
	this->_shouldMoveSide = shouldMoveSide;
	this->speed = 2;
	this->canFireLazers = true;
}



void BossShip::update(Graphics &graphics) {
	if (((int) this->getX()) % 100 == 0 && this->getInStartPos()){
		//EnemyShip* e = dynamic_cast<EnemyShip*>(enemy);
		this->fireLazer(graphics, 100, 100);
    }
	Enemy::update();
}


void BossShip::draw(Graphics &graphics) {
	Enemy::draw(graphics);
}



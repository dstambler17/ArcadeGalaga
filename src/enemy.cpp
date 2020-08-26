#include "headers/enemy.h"


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
	Sprite::update();
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
}

void EnemyShip::update() {
	Enemy::update();
}


void EnemyShip::draw(Graphics &graphics) {
	Enemy::draw(graphics);
}



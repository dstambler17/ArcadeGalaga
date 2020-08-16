#include "headers/enemy.h"

//Base enemy class
Enemy::Enemy() {}

Enemy::Enemy(Graphics &graphics, std::string filePath, int spawnX, int spawnY,
			int width, int height):
				Sprite(graphics, filePath, width, height, spawnX, spawnY)
{}

void Enemy::update() {
	Sprite::update();
}

void Enemy::loseHealth(int damage){
	this->health -= damage;
}

void Enemy::draw(Graphics &graphics) {
	Sprite::draw(graphics, this->_x, this->_y);
}


//Bat class
EyeBot::EyeBot() {}

EyeBot::EyeBot(Graphics &graphics, int spawnX, int spawnY):
		Enemy(graphics, "content/sprites/eyebot.png", spawnX, spawnY, 32, 32),
		_startingX(spawnX),
		_startingY(spawnY),
		_shouldMoveSide(true)
{
	this->health = 1;
}

void EyeBot::update() {
	if (this->_shouldMoveSide){
		if (this->_positiveDir){
			this->_x += 2;
		} else {
			this->_x -= 2;
		}
		
		this->_positiveDir = (this->_x < 700 && this->_x > 10) ? this->_positiveDir: !this->_positiveDir;

	}
	Enemy::update();
}


void EyeBot::draw(Graphics &graphics) {
	Enemy::draw(graphics);
}



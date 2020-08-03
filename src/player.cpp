#include "headers/player.h"
#include "headers/graphics.h"
#include "headers/lazer.h"

#include <string>
#include <iostream>
#include <vector>
using std::vector;

namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float JUMP_SPEED = 0.7f;

	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
    const int NUM_LAZERS_PER_SCREEN = 0;
}

Player::Player() {}

Player::Player(Graphics &graphics):
Sprite(graphics, "content/sprites/Ship1.png", 50, 50, 300, 400),
_dx(0),
_dy(0),
numLazers(player_constants::NUM_LAZERS_PER_SCREEN)
{}



const float Player::getX() const {
	return this->_x;
}

const float Player::getY() const {
	return this->_y;
}

void Player::moveLeft() {
    this->_dx -= 10;
}

void Player::moveRight() {
    this->_dx = 10;
}

void Player::moveUp() {
    this->_dy = -10;
}

void Player::moveDown() {
    this->_dy = 10;
}

void Player::fireLazer(Graphics &graphics){
    std::cout << "CREATION" << std::endl;
    this->_lazers.push_back(Lazer(graphics, true, this->_x + 15, this->_y));
    std::cout << "CREATION SUCCESS" << std::endl;
    this->numLazers += 1;
}


void Player::update() {
    this->_x += this->_dx;
	this->_y += this->_dy;
    this->_dx = 0;
    this->_dy = 0;
    if (this->numLazers > 0){
        for (Lazer &lazer : this->_lazers){
            //std::cout << "steve" << std::endl;
            lazer.travel();
            lazer.update();
        }
        //std::cout << "end" << std::endl;   
    }
}

void Player::draw(Graphics &graphics) {
	Sprite::draw(graphics, this->_x, this->_y);
    if (this->numLazers > 0){
        for (Lazer &lazer : this->_lazers){
            lazer.draw(graphics);
        }   
    }
}

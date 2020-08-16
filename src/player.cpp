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
    const float STARTING_HEALTH = 3;
    const int NUM_LAZERS_PER_SCREEN = 0;
}

Player::Player() {}

Player::Player(Graphics &graphics):
Sprite(graphics, "content/sprites/Ship1.png", 50, 50, 300, 400),
_dx(0),
_dy(0),
invincibilityOn(false),
health(player_constants::STARTING_HEALTH),
numLazers(player_constants::NUM_LAZERS_PER_SCREEN)
{
    SDL_Surface* heartSurface = graphics.loadImage("content/sprites/heart.png");
    this->_healthTex = SDL_CreateTextureFromSurface(graphics.getRenderer(), heartSurface);
}



const float Player::getX() const {
	return this->_x;
}

const float Player::getY() const {
	return this->_y;
}

const int Player::getHealth() const {
	return this->health;
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
    this->_lazers.push_back(Lazer(graphics, true, this->_x + 15, this->_y));
    this->numLazers += 1;
}


void Player::update() {
    this->_x += this->_dx;
	this->_y += this->_dy;
    this->_dx = 0;
    this->_dy = 0;

    //Handle invincibility frames
    if (this->invincibilityOn){
        this->invincibilityFrame -= 1;
    }
    if (this->invincibilityFrame == 0){
        this->invincibilityOn = false;
    }

    vector<int> deleteIdx;
    if (this->numLazers > 0){
        int i = 0;
        for (Lazer &lazer : this->_lazers){
            if (lazer.getY() >= -20){
                lazer.travel();
                lazer.update();
            } else{
                deleteIdx.push_back(i);
                std::cout << this->_lazers.size() << std::endl;
            }
            i += 1;
        }
    }
    //Remove Lazers that are no longer used
    for (int idx : deleteIdx){
       this->_lazers.erase(this->_lazers.begin() + idx);
    }
    deleteIdx.clear();
    Sprite::update();
}

void Player::handleEnemyCollisions(Enemy &enemy) {
    std::cout << "COLLISION TEST" << std::endl;
    if (!this->invincibilityOn){
        this->health -= 1;
        this->invincibilityOn = true;
        this->invincibilityFrame = 50;
    }
	
}

void Player::draw(Graphics &graphics) {
	Sprite::draw(graphics, this->_x, this->_y);
    if (this->numLazers > 0){
        for (Lazer &lazer : this->_lazers){
            lazer.draw(graphics);
        }   
    }
    SDL_Rect heart = {0,0,25,25};
    for (int c = 0; c < this->health; c++){
        heart.x = c * 25;
        graphics.blitSurface(this->_healthTex, NULL, &heart);
    }
}

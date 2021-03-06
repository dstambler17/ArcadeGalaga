#include "headers/player.h"
#include "headers/graphics.h"
#include "headers/lazer.h"

#include <string>
#include <iostream>
#include <vector>
using std::vector;

namespace player_constants {
	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
    const float STARTING_HEALTH = 3;
    const int NUM_LAZERS_PER_SCREEN = 0;
    const int SCREEN_WIDTH = 750;
    const int SCREEN_HIGHT = 550;
    const int RECHARGE_TIME = 10;
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
    this->score = 0;
    this->rechargeTime = 0;
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
    if (this->rechargeTime == 0){
        this->_lazers.push_back(Lazer(graphics, true, this->_x + 15, this->_y, "content/sprites/lazer.png"));
        this->numLazers += 1;
        this->rechargeTime = player_constants::RECHARGE_TIME;
    }
    
}

void Player::setPlayerStartPos(){
    this->setPlayerScore(0);
    this->setPlayerHealth(3);
    this->clearLazers();
    this->_x = 300;
    this->_y = 400;
}


void Player::update() {
    if (this->_dx + this->_x <= player_constants::SCREEN_WIDTH && this->_dx + this->_x >= 0){
        this->_x += this->_dx;
    }
    if (this->_dy + this->_y <= player_constants::SCREEN_HIGHT && this->_dy + this->_y >= 0){
        this->_y += this->_dy;
    }
	
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
            if (lazer.getY() >= -5){
                lazer.travel();
                lazer.update();
            } else{
                deleteIdx.push_back(i);
                //std::cout << this->_lazers.size() << std::endl;
            }
            i += 1;
        }
    }

    //Remove Lazers that are no longer used
    for (int idx : deleteIdx){
       this->_lazers.erase(this->_lazers.begin() + idx);
    }
    deleteIdx.clear();
    if (this->rechargeTime > 0){
        this->rechargeTime -= 1;
    }
    Sprite::update();
}

void Player::handleEnemyCollisions() {
    if (!this->invincibilityOn){
        this->health -= 1;
        this->invincibilityOn = true;
        this->invincibilityFrame = 50;
    }
}

void Player::handleLazerCollisions(Enemy* enemy) {
    //Collect Collided with enemies
    
    if (this->numLazers > 0){
        int i = 0;
        //Note, using an iterator is a much better way to handle
        auto it = this->_lazers.begin();
        while (it != this->_lazers.end())
        {   
            Lazer lazer = *it;
            if (lazer.getBoundingBox().collidesWith(enemy->getBoundingBox())){
                lazer.collideWithEnemy(enemy);
                it = this->_lazers.erase(it);
            } else{
                ++it;
            }
        }
        
    }
}

void Player::updateScore(int points){
    this->score += points;
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

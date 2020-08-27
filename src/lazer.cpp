#include "headers/lazer.h"
#include "headers/graphics.h"

#include <string>
#include <iostream>



Lazer::Lazer(Graphics &graphics, bool travelingUp, int start_x, int start_y, std::string lazerPath):
Sprite(graphics, lazerPath, 20, 25, start_x, start_y),
_dx(start_x),
_dy(start_y)
{   
    this->damage = 1;
    this->travelingUp = travelingUp;
}


void Lazer::travel() {
    if (this->travelingUp){
        this->_dy = -5;
    } else {
        this->_dy = 5;
    }
}


float Lazer::getY(){
    return this->_y;
}

void Lazer::collideWithEnemy(Enemy* enemy){
    enemy->loseHealth(this->damage);
}

void Lazer::update() {
    this->_y += this->_dy;
    Sprite::update();
}

void Lazer::draw(Graphics &graphics) {
	Sprite::draw(graphics, this->_x, this->_y);
}

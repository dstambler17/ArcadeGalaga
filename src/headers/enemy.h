#ifndef ENEMY_H
#define ENEMY_H

#include "headers/sprite.h"
#include "headers/player.h"

#include <string>

class Graphics;

class Enemy : public Sprite {
public:
	Enemy();
	Enemy(Graphics &graphics, std::string filePath, int spawnX, int spawnY,
			int width, int height);
	virtual void update();
	virtual void draw(Graphics &graphics);
};


class EyeBot : public Enemy {
public:
	EyeBot();
	EyeBot(Graphics &graphics, int spawnX, int spawnY);
	void update();
	void draw(Graphics &graphics);

private:
	float _startingX, _startingY;
	bool _shouldMoveSide;
};


#endif

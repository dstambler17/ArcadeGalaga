#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "player.h"

#include <string>

class Graphics;

class Enemy : public Sprite {
public:
	Enemy();
	Enemy(Graphics &graphics, std::string filePath, int spawnX, int spawnY,
			int width, int height, int startY);
	virtual void update();
	virtual void draw(Graphics &graphics);

	void loseHealth(int damage);

	/*Function that moves enemies down into their starting pos */
	void moveToStart();
	int getHealth() {return this->health;}
	int getPoints() {return this->points;}

protected:
	int health;
	int points;
	int trueStart;
	int speed;
	bool inStartingPos;
	bool _shouldMoveSide;
	bool _positiveDir;
};


class EyeBot : public Enemy {
public:
	EyeBot();
	EyeBot(Graphics &graphics, int spawnX, int spawnY, bool shouldMoveSide);
	void update();
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};



class UFO : public Enemy {
public:
	UFO();
	UFO(Graphics &graphics, int spawnX, int spawnY, bool shouldMoveSide);
	void update();
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};


class EnemyShip : public Enemy {
public:
	EnemyShip();
	EnemyShip(Graphics &graphics, int spawnX, int spawnY, bool shouldMoveSide);
	void update();
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};


#endif

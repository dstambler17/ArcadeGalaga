#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "player.h"
#include "lazer.h"
#include <vector>
using std::vector;

#include <string>

class Graphics;
class Lazer;
class Player;

class Enemy : public Sprite {
public:
	Enemy();
	Enemy(Graphics &graphics, std::string filePath, int spawnX, int spawnY,
			int width, int height, int startY);
	virtual void update(Graphics &graphics);
	virtual void update();
	virtual void draw(Graphics &graphics);

	void handleLazerCollisions(Player* player);
	void loseHealth(int damage);

	/*Function that moves enemies down into their starting pos */
	void moveToStart();

	/*Not all enemies can do this but w.e*/
	void fireLazer(Graphics &graphics);


	int getHealth() {return this->health;}
	int getPoints() {return this->points;}
	bool getInStartPos() { return this->inStartingPos; }
	float getX() {return this->_x;}
	bool getCanFireLazers() {return this->canFireLazers;}

protected:
	int health;
	int points;
	int trueStart;
	int speed;
	bool inStartingPos;
	bool _shouldMoveSide;
	bool _positiveDir;
	bool canFireLazers = false;
	vector<Lazer> _lazers;
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
	void update(Graphics &graphics);
	void draw(Graphics &graphics);


private:
	float _startingX, _startingY;
};


#endif

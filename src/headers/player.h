#ifndef PLAYER_H
#define PLAYER_H

#include "rectangle.h"
#include "sprite.h"
#include "lazer.h"
#include <vector>
using std::vector;


class Graphics;
class Enemy;
class Lazer;

class Player : Sprite {
public:
	Player();
	Player(Graphics &graphics);
	void draw(Graphics &graphics);
	void update();

	/* void moveLeft
	 * Moves the player left by -dx
	 */
	void moveLeft();

	/* void moveRight
	 * Moves the player right by dx
	 */
	void moveRight();

    /* void moveUp
	 * Moves the player up by dx
	 */
    void moveUp();

    /* void moveDown
	 * Moves the player down by dx
	 */
    void moveDown();

    void fireLazer(Graphics &graphics);
	void updateScore(int points);

	void handleEnemyCollisions();
	void handleLazerCollisions(Enemy* enemy);

	const Rectangle getBoundingBox() {
		return Sprite::getBoundingBox();
	}

	const float getX() const;
	const float getY() const;
	const int getHealth() const;
	int getPlayerScore() { return this->score; }
	void setPlayerScore(int num) { this->score = num; }
	void setPlayerHealth(int num) { this->health = num; }
	void clearLazers() { this->numLazers = 0; this->_lazers.clear(); }
	void setPlayerStartPos();


private:
	float _dx, _dy;
    int numLazers;
	int health;
	int invincibilityOn;
	int invincibilityFrame;
	int score;
	int score_multiplier;
	int rechargeTime;

	SDL_Texture* _healthTex;
    vector<Lazer> _lazers;

};

#endif

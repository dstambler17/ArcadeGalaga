#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "lazer.h"
#include <vector>
using std::vector;


class Graphics;

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


	const float getX() const;
	const float getY() const;

private:
	float _dx, _dy;
    int numLazers;
    vector<Lazer> _lazers;
};

#endif

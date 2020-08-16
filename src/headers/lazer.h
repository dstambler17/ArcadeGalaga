#ifndef LAZER_H
#define LAZER_H

#include "rectangle.h"
#include "sprite.h"
#include "enemy.h"

class Graphics;
class Enemy;

class Lazer : public Sprite {
public:
	Lazer(Graphics &graphics, bool travelingUp, int start_x, int start_y);
	void draw(Graphics &graphics);
	void update();

	/* void travel
	 * Moves the lazer in its direction by dx
	 */
	void travel();
	void collideWithEnemy(Enemy* enemy);

	const Rectangle getBoundingBox() {
		return Sprite::getBoundingBox();
	}

	const float getX() const;
	float getY();

private:
	float _dx, _dy;
	int damage;
    bool travelingUp;
};

#endif

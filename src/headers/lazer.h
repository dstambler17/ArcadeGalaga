#ifndef LAZER_H
#define LAZER_H

#include "sprite.h"

class Graphics;

class Lazer : public Sprite {
public:
	Lazer(Graphics &graphics, bool travelingUp, int start_x, int start_y);
	void draw(Graphics &graphics);
	void update();

	/* void travel
	 * Moves the lazer in its direction by dx
	 */
	void travel();


	const float getX() const;
	float getY();

private:
	float _dx, _dy;
    bool travelingUp;
};

#endif

#ifndef SPRITE_H
#define SPRITE_H
class Graphics;

/* Sprite class
 * Holds all information for individual sprites
 */
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class Sprite {
public:
    Sprite();
	Sprite(Graphics &graphics, std::string filePath, int width, int height, int x_start, int y_start);
	virtual ~Sprite();
	virtual void update();
	void draw(Graphics &graphics, int x_pos, int y_pos);


	const inline float getX() const { return this->_x; }
	const inline float getY() const { return this->_y; }

protected:
	SDL_Rect _sourceRect, _destRect;
	SDL_Texture* _spriteTex;

	float _x, _y;
private:
};


#endif
#pragma once

#include "MovingObject.h"

class Obstacle : public MovingObject
{
public:
	Obstacle(const sf::Texture& data, bool dir, int size, int row, int col);
	~Obstacle();

private:

};
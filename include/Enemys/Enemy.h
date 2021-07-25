#pragma once

#include "MovingObject.h"

class Enemy : public MovingObject
{
public:
	Enemy(const sf::Texture& data, bool dir, int size, int row, int col);
	~Enemy();
private:

};
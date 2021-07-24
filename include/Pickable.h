#pragma once

#include "MovingObject.h"

class Pickable : public MovingObject
{
public:
	Pickable(const sf::Texture& data, bool dir, int size, int row, int col);
	~Pickable();
private:

};
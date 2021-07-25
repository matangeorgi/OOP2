#pragma once

#include "MovingObject.h"

class Brick : public MovingObject
{
public:
	Brick(int row, int col);

	virtual void move(sf::Time deltaTime) override;
	~Brick();
private:
};
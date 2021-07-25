#pragma once

#include "MovingObject.h"

class Platforms : public MovingObject
{
public:
	Platforms(int row, int col);
	void move(sf::Time deltaTime) override;
	~Platforms();
private:
};
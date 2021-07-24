#pragma once

#include "MovingObject.h"

class Fireworks : public MovingObject
{
public:
	Fireworks(sf::Vector2f playerPos, bool direction);

	virtual void move(sf::Time deltaTime) override;
	~Fireworks();
private:
};
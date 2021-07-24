#pragma once

#include "Enemy.h"

class PiranaPlants : public Enemy
{
public:
	PiranaPlants(int row, int col);

	virtual void move(sf::Time deltaTime) override;
	~PiranaPlants();
private:
};
#pragma once

#include "Enemy.h"

class FlyingTortoise : public Enemy
{
public:
	FlyingTortoise(int row, int col);

	void move(sf::Time deltaTime) override;
	virtual void handleDeath(sf::Time deltaTime) override;
	~FlyingTortoise();
private:
};
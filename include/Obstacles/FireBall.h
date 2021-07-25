#pragma once

#include "Obstacle.h"

class FireBall : public Obstacle
{
public:
	FireBall(int row, int col);

	void move(sf::Time deltaTime) override;
	~FireBall();
private:
	void changeSpriteDirection();
};
#pragma once

#include "Obstacle.h"

class FirePole : public Obstacle
{
public:
	FirePole(int row, int col);

	virtual void move(sf::Time deltaTime) override;
private:
	float m_timePassed,
		m_angle;
};
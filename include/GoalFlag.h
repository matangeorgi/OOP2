#pragma once

#include "MovingObject.h"

class GoalFlag : public MovingObject
{
public:
	GoalFlag(int row, int col);

	void setShouldMove(); 
	virtual bool isShouldMove() const override;
	virtual void move(sf::Time deltaTime) override;
	~GoalFlag();

private:
};
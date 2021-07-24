#pragma once

#include "Enemy.h"

class BadMushroom : public Enemy
{
public:
	BadMushroom(int row, int col);

	void move(sf::Time deltaTime) override;
	~BadMushroom();
private:
};
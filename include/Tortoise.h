#pragma once

#include "Enemy.h"

class Tortoise : public Enemy
{
public:
	Tortoise(int row, int col);

	void setShell();
	bool getShell() const;
	bool getJumped() const;
	void setJumped(bool condition);
	void setDirection(float playerPosX);
	virtual void move(sf::Time deltaTime) override;
	~Tortoise();

private:
	bool m_shell,
		m_jumped;
};
#pragma once

#include "Pickable.h"
#include "Animation.h"

class Coin : public Pickable
{
public:
	Coin(int row, int col);

	void setTaken();
	bool getTaken() const;
	virtual void move(sf::Time deltaTime);

	~Coin();
private:
	bool m_taken;
};
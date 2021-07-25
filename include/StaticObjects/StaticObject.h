#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject(int row, int col);
	virtual void shift(sf::Time deltaTime);
	~StaticObject();
private:

};
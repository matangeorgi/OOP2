#include "Obstacle.h"

Obstacle::Obstacle(const sf::Texture& data, bool dir, int size, int row, int col) :
	MovingObject(data, dir,size,row,col)
{
}

//-----------------------------------------------------------------------------
Obstacle::~Obstacle()
{
}

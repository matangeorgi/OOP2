#include "Enemy.h"

Enemy::Enemy(const sf::Texture& data, bool dir, int size, int row, int col)
	: MovingObject(data, dir, size,row,col)
{
}

//-----------------------------------------------------------------------------
Enemy::~Enemy()
{
}

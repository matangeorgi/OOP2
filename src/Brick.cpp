#include "Brick.h"

Brick::Brick(int row, int col) :
	MovingObject(TextureHolder::instance().getTextures(BRICK), RIGHT, 1, row, col)
{
	m_sprite.setScale(BRICK_SCALE, BRICK_SCALE);
	m_lastPos = getPos();
	m_shouldMove = false;
}

//-----------------------------------------------------------------------------
void Brick::move(sf::Time deltaTime)
{
	if (m_shouldMove)
		squareMove(deltaTime);
}

//-----------------------------------------------------------------------------
Brick::~Brick()
{
}

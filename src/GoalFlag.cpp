#include "GoalFlag.h"

GoalFlag::GoalFlag(int row, int col) :
	MovingObject(TextureHolder::instance().getFlag(I_FLAG), LEFT, 1, row, col)
{
	m_sprite.setPosition((float)(col * ICON_SIZE + FLAG_X_POS), (float)(((row+ FLAG_Y_POS) * ICON_SIZE)));
	m_sprite.setScale(1, 1);
	m_lastPos = getPos();
	m_shouldMove = false;
}

//-----------------------------------------------------------------------------
void GoalFlag::move(sf::Time deltaTime)
{
	if (m_shouldMove)
	{
		if (getPos().y - m_lastPos.y < FLAG_DISTANCE * ICON_SIZE)
		{
			m_velocity.y = ENEMY_SPEED * deltaTime.asSeconds();
			m_sprite.move(m_velocity);
		}
		else
			m_velocity.y = 0;
	}
}

//-----------------------------------------------------------------------------
void GoalFlag::setShouldMove()
{
	m_shouldMove = true;
}

//-----------------------------------------------------------------------------
bool GoalFlag::isShouldMove() const
{
	return true;
}

//-----------------------------------------------------------------------------
GoalFlag::~GoalFlag()
{
}

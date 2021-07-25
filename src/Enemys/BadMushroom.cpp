#include "BadMushroom.h"

BadMushroom::BadMushroom(int row, int col)
	: Enemy(TextureHolder::instance().getEnemy(I_BADMUSHROOM), LEFT, BAD_MUSH_SIZE, row ,col)
{
}

//-----------------------------------------------------------------------------
void BadMushroom::move(sf::Time deltaTime)
{
	if (!m_dead)
	{
		sideMove(deltaTime, ENEMY_SPEED);
		m_animation.staticShift(deltaTime, SWITCH);
		m_animation.setDirection(m_dir);	
	}
	else if (m_tortoiseKill)
		handleDeathTortoise(deltaTime);

	else
		handleDeath(deltaTime);
}

//-----------------------------------------------------------------------------
BadMushroom::~BadMushroom()
{
}


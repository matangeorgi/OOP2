#include "FlyingTortoise.h"

FlyingTortoise::FlyingTortoise(int row, int col)
	: Enemy(TextureHolder::instance().getEnemy(I_F_TORTOISE), RIGHT, F_TORTOISE_SIZE,row,col)
{
}

//-----------------------------------------------------------------------------
void FlyingTortoise::move(sf::Time deltaTime)
{
	if (!m_dead)
		upDownMove(deltaTime, ENEMY_SPEED, MAX_HEIGHT, MIN_HEIGHT, SWITCH);
	else
		handleDeath(deltaTime);
}

//-----------------------------------------------------------------------------
void FlyingTortoise::handleDeath(sf::Time deltaTime)
{
	if (m_deathTimePassed == 0)
		m_velocity.y = 0;

	fall(deltaTime);
	m_sprite.move(m_velocity);
	m_deathTimePassed += deltaTime.asSeconds();

	// His death is ended
	if (m_deathTimePassed > DEATH_TIME)
		isDelete();
}

//-----------------------------------------------------------------------------
FlyingTortoise::~FlyingTortoise()
{
}

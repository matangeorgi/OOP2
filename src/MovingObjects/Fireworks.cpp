#include "Fireworks.h"

Fireworks::Fireworks(sf::Vector2f playerPos, bool direction):
	MovingObject(TextureHolder::instance().getTextures(FIREWORKS), direction, FIRE_SIZE,0,0)
{
	if (direction)
		m_sprite.setPosition(playerPos.x + ICON_SIZE, playerPos.y + FIREWORK_Y_POS);
	else
		m_sprite.setPosition(playerPos.x, playerPos.y + FIREWORK_Y_POS);

	m_dir = direction;
}

//-----------------------------------------------------------------------------
// Special move making the firework bump
void Fireworks::move(sf::Time deltaTime)
{
	if (m_dead)
	{
		m_deathTimePassed += deltaTime.asSeconds();

		if (m_deathTimePassed > SWITCH)
			m_delete = true;
		return;
	}

	m_velocity.x = FIREWORKS_SPEED * deltaTime.asSeconds();
	if (!m_dir)
		m_velocity.x *= -1;

	fall(deltaTime);
	m_sprite.move(m_velocity);
}

//-----------------------------------------------------------------------------
Fireworks::~Fireworks()
{
}


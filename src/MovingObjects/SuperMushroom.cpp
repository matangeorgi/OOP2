#include "SuperMushroom.h"

SuperMushroom::SuperMushroom(int row, int col) : m_kind(false), m_rising(true),
Pickable(TextureHolder::instance().getTextures(SUPER_MUSH), RIGHT,1, row, col)
{
	m_sprite.setPosition((float)(col * ICON_SIZE), 
		                 (float)((row * ICON_SIZE + ICON_SIZE)));
	m_lastPos = m_sprite.getPosition();
	m_shouldMove = false;
} 

//-----------------------------------------------------------------------------
void SuperMushroom::move(sf::Time deltaTime)
{
	m_dead = false;
	if (std::abs(getPos().y - m_lastPos.y) < ICON_SIZE && m_rising)
	{
		m_velocity.y = -deltaTime.asSeconds() * ENEMY_SPEED;
		m_sprite.move(m_velocity);
	}
	else if (!m_kind) // SuperMushroom
	{
		m_lastPos.y = getPos().y;
		sideMove(deltaTime, ENEMY_SPEED * FALLING_VEL);
		m_rising = false;
	}
}

//-----------------------------------------------------------------------------
void SuperMushroom::setKind(bool kind)
{
	m_kind = kind;

	if (kind)
		m_sprite.setTexture(TextureHolder::instance().getTextures(FIRE_FLOWER));
}

//-----------------------------------------------------------------------------
bool SuperMushroom::getKind() const
{
	return m_kind;
}

//-----------------------------------------------------------------------------
void SuperMushroom::setShouldMove()
{
	m_shouldMove = true;
	m_velocity.y = -1;
	m_sprite.move(m_velocity);
}
//-----------------------------------------------------------------------------
SuperMushroom::~SuperMushroom()
{
}


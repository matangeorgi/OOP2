#include "FirePole.h"
#include <iostream>
FirePole::FirePole(int row, int col)
	: Obstacle(TextureHolder::instance().getTextures(FIRE_POLE), LEFT, 1,row,col),m_timePassed(0),m_angle(0)
{
	m_sprite.setPosition((float)(col * ICON_SIZE + 7), (float)((row * ICON_SIZE) - ICON_SIZE/1.8));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getOrigin().y + ICON_SIZE);
	m_firePole = true;
}

//-----------------------------------------------------------------------------
void FirePole::move(sf::Time deltaTime)
{
	m_sprite.rotate(deltaTime.asSeconds() * FIREPOLE_SPEED);

	m_timePassed += deltaTime.asSeconds();
	if (m_timePassed > FIRE_POLE_SWITCH)
	{
		m_sprite.setScale(m_sprite.getScale().x * -1, m_sprite.getScale().y);
		m_timePassed -= SWITCH;
	}
}
#include "FireBall.h"

const float jumpDeceleration = 0.5f;
const float jumpStart = -0.55f;

FireBall::FireBall(int row, int col)
	: Obstacle(TextureHolder::instance().getTextures(FIRE_BALL), LEFT, 1,row,col)
{
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_sprite.setPosition((float)(col * ICON_SIZE), (float)((VIEW_HEIGHT + ICON_SIZE)));
	m_sprite.setScale(m_sprite.getScale().x, m_sprite.getScale().y * -1);
}

//-----------------------------------------------------------------------------
void FireBall::move(sf::Time deltaTime)
{

	if (getPos().y >= VIEW_HEIGHT + ICON_SIZE)
		m_sprite.setPosition(getPos().x, VIEW_HEIGHT + ICON_SIZE);

	if (getPos().y == VIEW_HEIGHT + ICON_SIZE)
		m_velocity.y = jumpStart;

	else 
		m_velocity.y += jumpDeceleration * deltaTime.asSeconds();

	m_sprite.move(m_velocity);
	changeSpriteDirection();
}

//-----------------------------------------------------------------------------
void FireBall::changeSpriteDirection()
{
	if (m_velocity.y < 0 && !m_dir ||
		m_velocity.y > 0 && m_dir)
	{
		m_sprite.setScale(m_sprite.getScale().x, m_sprite.getScale().y * -1);
		m_dir = !m_dir;
	}
}

//-----------------------------------------------------------------------------
FireBall::~FireBall()
{
}
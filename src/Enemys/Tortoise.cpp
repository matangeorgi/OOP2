#include "Tortoise.h"

Tortoise::Tortoise(int row, int col)
	: Enemy(TextureHolder::instance().getEnemy(I_TORTOISE), LEFT, TORTOISE_SIZE, row ,col),
	m_shell(false), m_jumped(false)
{
	m_sprite.setPosition((float)(col * ICON_SIZE),
						 (float)((row * ICON_SIZE)) + TORTOISE_Y_POS);
}

//-----------------------------------------------------------------------------
void Tortoise::move(sf::Time deltaTime)
{
	if (!m_shell)
	{
		sideMove(deltaTime, ENEMY_SPEED);
		m_animation.staticShift(deltaTime, SWITCH);
		m_animation.setDirection(m_dir);
	}

	else if (m_jumped)
		sideMove(deltaTime, SHELL_SPEED);

	if (m_tortoiseKill)
		handleDeathTortoise(deltaTime);
}

//-----------------------------------------------------------------------------
void Tortoise::setShell()
{
	m_shell = true;
	m_animation.setDeadSprite();
}

//-----------------------------------------------------------------------------
bool Tortoise::getShell() const
{
	return m_shell;
}

//-----------------------------------------------------------------------------
void Tortoise::setJumped(bool condition)
{
	m_jumped = condition;
}

//-----------------------------------------------------------------------------
bool Tortoise::getJumped() const
{
	return m_jumped;
}

//-----------------------------------------------------------------------------
void Tortoise::setDirection(float playerPosX)
{
	if (playerPosX > getPos().x)
		m_dir = LEFT;
	else
		m_dir = RIGHT;
}

//-----------------------------------------------------------------------------
Tortoise::~Tortoise()
{
}
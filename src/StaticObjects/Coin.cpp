#include "Coin.h"

Coin::Coin(int row, int col) :m_taken(false),
Pickable(TextureHolder::instance().getTextures(COIN), LEFT, COIN_SIZE, row, col)
{
	m_sprite.setPosition((float)(col * ICON_SIZE + COIN_X_POS),
						 (float)(((row+1) * ICON_SIZE + COIN_Y_POS)));
	m_lastPos = getPos();
}

//-----------------------------------------------------------------------------
void Coin::move(sf::Time deltaTime)
{
	m_animation.staticShift(deltaTime, COIN_SWITCH);
	if (m_taken)
	{
		squareMove(deltaTime);
		if (getPos().y >= m_lastPos.y)
			m_delete = true;
	}
}

//-----------------------------------------------------------------------------
// This function let us know when the coin has been collected
void Coin::setTaken()
{
	m_taken = true;
	m_velocity.y = BUMP;
	m_sprite.move(m_velocity);
}

//-----------------------------------------------------------------------------
bool Coin::getTaken() const
{
	return m_taken;
}

//-----------------------------------------------------------------------------
Coin::~Coin()
{
}

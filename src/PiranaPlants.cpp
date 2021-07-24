#include "PiranaPlants.h"

PiranaPlants::PiranaPlants(int row, int col)
	: Enemy(TextureHolder::instance().getEnemy(I_PIRANA), LEFT, PIRANA_SIZE,row,col)
{
	m_sprite.setScale(PIRANA_SCALE, PIRANA_SCALE);
	m_sprite.setPosition((float)(col * ICON_SIZE+ PIPE_X_POS),
		                 (float)((row * ICON_SIZE + PIPE_Y_POS)));
	m_lastPos = m_sprite.getPosition();
}

//-----------------------------------------------------------------------------
void PiranaPlants::move(sf::Time deltaTime)
{
	if (m_dead)
		m_delete = true;
	upDownMove(deltaTime, PIRANA_SPEED, m_lastPos.y, m_lastPos.y + ICON_SIZE * PIRANA_MOV, SWITCH_PIRANA);
}

//-----------------------------------------------------------------------------
PiranaPlants::~PiranaPlants()
{
}

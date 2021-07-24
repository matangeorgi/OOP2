#include "Platforms.h"

Platforms::Platforms(int row, int col)
	: MovingObject(TextureHolder::instance().getTextures(PLATFORM), LEFT, 1,row,col)
{
	m_sprite.setScale(PLAT_X_SCALE, PLAT_Y_SCALE);
}

//-----------------------------------------------------------------------------
void Platforms::move(sf::Time deltaTime)
{
	upDownMove(deltaTime,ENEMY_SPEED,MAX_HEIGHT,MIN_HEIGHT,SWITCH);
}

//-----------------------------------------------------------------------------
Platforms::~Platforms()
{
}

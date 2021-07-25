#include "Floor.h"

Floor::Floor(int row, int col): UnPickable(row,col)
{
	m_sprite.setTexture(TextureHolder::instance().getTextures(FLOOR));
	m_sprite.setScale(FLOOR_SCALE, FLOOR_SCALE);
}

//-----------------------------------------------------------------------------
Floor::~Floor()
{
}

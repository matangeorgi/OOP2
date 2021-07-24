#include "Block.h"

Block::Block(int row, int col) : UnPickable(row,col)
{
	m_sprite.setTexture(TextureHolder::instance().getTextures(BLOCK));
	m_sprite.setScale(BLOCK_SCALE, BLOCK_SCALE);
}

//-----------------------------------------------------------------------------
Block::~Block()
{ 
}

#include "Pipe.h"

Pipe::Pipe(int row, int col):UnPickable(row,col)
{
	m_sprite.setTexture(TextureHolder::instance().getTextures(PIPE));
	m_sprite.setScale(PIPE_SCALE, PIPE_SCALE);
}

//-----------------------------------------------------------------------------
Pipe::~Pipe()
{
}

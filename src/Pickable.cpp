#include "Pickable.h"

Pickable::Pickable(const sf::Texture& data, bool dir, int size, int row, int col):
  MovingObject(data, dir, size, row, col)
{
}

//-----------------------------------------------------------------------------
Pickable::~Pickable()
{
}

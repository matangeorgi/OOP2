#include "GameObject.h"

GameObject::GameObject(int row, int col): m_delete(false),m_firePole(false)
{
	m_sprite.setScale(SCALE, SCALE);
	m_sprite.setPosition((float)(col * ICON_SIZE), (float)((row * ICON_SIZE)));
}

//-----------------------------------------------------------------------------
const sf::Sprite& GameObject::draw() const
{
	return m_sprite;
}

//-----------------------------------------------------------------------------
bool GameObject::isDelete() const
{
	return m_delete;
}

//-----------------------------------------------------------------------------
void GameObject::setDelete()
{
	m_delete = true;
}

//-----------------------------------------------------------------------------
sf::Vector2f GameObject::getPos() const
{
	return m_sprite.getPosition();
}

//-----------------------------------------------------------------------------
bool GameObject::isFirePole() const
{
	return m_firePole;
}




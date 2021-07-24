#pragma once

#include "TextureHolder.h"
#include "AudioHolder.h"

class GameObject
{
public:
	GameObject(int row, int col);

	sf::Vector2f getPos() const;
	bool isFirePole() const;
	const sf::Sprite& draw() const;
	bool isDelete() const;
	void setDelete();
	virtual ~GameObject() = default;

protected:
	sf::Sprite m_sprite;
	bool m_delete,
		m_firePole;

private:
};
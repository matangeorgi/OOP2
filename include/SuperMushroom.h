#pragma once

#include "Pickable.h"

class SuperMushroom : public Pickable
{
public:
	SuperMushroom(int row, int col);

	void setShouldMove();
	bool getKind() const;
	void setKind(bool kind);
	virtual void move(sf::Time deltaTime);
	~SuperMushroom();

private:
	bool m_kind,
		m_rising;
};
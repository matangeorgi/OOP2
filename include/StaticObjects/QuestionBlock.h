#pragma once

#include "MovingObject.h"

class QuestionBlock : public MovingObject
{
public:
	QuestionBlock(int row, int col);

	bool isOpen() const;
	bool getKind() const;
	void setOpen(bool kind);
	virtual void move(sf::Time deltaTime) override;
	virtual bool isShouldMove() const override;
	~QuestionBlock();

private:
	bool m_open,
		m_finished,
		m_kind;	// This var stores the player state in order to choose what to pull out
};
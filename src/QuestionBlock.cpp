#include "QuestionBlock.h"

QuestionBlock::QuestionBlock(int row, int col) :m_open(false),m_finished(false),m_kind(true),
	MovingObject(TextureHolder::instance().getTextures(QUESTION), RIGHT, QUESTION_SIZE, row, col)
{
	m_sprite.setScale(QUESTION_SCALE, QUESTION_SCALE);
	m_lastPos = getPos();
	m_shouldMove = false;
}

//-----------------------------------------------------------------------------
void QuestionBlock::move(sf::Time deltaTime)
{
	if (m_open && !m_finished)
	{
		if (m_velocity.y == 0)
			m_finished = true;

		if (m_shouldMove)
			squareMove(deltaTime);
		m_animation.setDeadSprite();
	}

	if (!m_open && !m_finished)
	{
		m_animation.staticShift(deltaTime, SWITCH);
		m_animation.setDirection(m_dir);
	}
}

//-----------------------------------------------------------------------------
bool QuestionBlock::isShouldMove() const
{
	return true;
}

//-----------------------------------------------------------------------------
bool QuestionBlock::getKind() const
{
	return m_kind;
}

//-----------------------------------------------------------------------------
void QuestionBlock::setOpen(bool kind) 
{
	m_open = true;
	m_kind = kind;
}

//-----------------------------------------------------------------------------
bool QuestionBlock::isOpen() const
{
	return m_open;
}

//-----------------------------------------------------------------------------
QuestionBlock::~QuestionBlock()
{
}





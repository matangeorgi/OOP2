#include "GoalPole.h"

GoalPole::GoalPole(int row, int col) : UnPickable(row, col), m_playerReached(false)
{
	m_sprite.setTexture(TextureHolder::instance().getFlag(I_POLE));
	m_sprite.setPosition((float)(col * ICON_SIZE), (float)((row * ICON_SIZE + POLE_Y_POS * ICON_SIZE)));
	m_sprite.setScale(POLE_SCALE, POLE_SCALE);
}

//-----------------------------------------------------------------------------
void GoalPole::setPlayerReached()
{
	if (!m_playerReached)
	{
		AudioHolder::instance().playSound(AUDIO_FINISH_STAGE);
		AudioHolder::instance().stopBGSound();
	}

	m_playerReached = true;
}

//-----------------------------------------------------------------------------
bool GoalPole::isPlayerReached() const
{
	return m_playerReached;
}

//-----------------------------------------------------------------------------
GoalPole::~GoalPole()
{
}

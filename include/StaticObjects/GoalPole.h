#pragma once

#include "UnPickable.h"

class GoalPole : public UnPickable
{
public:
	GoalPole(int row, int col);

	void setPlayerReached();
	bool isPlayerReached() const;
	~GoalPole();

private:
	bool m_playerReached;
};
#pragma once

#include "Board.h"
#include "GameWindow.h"

class Controller
{
public:
	Controller();

	void startMenu();
	~Controller();

private:

	void exitGame();
	void startGame();
	void openLeaderBoard();
	void handleLeaderBoard(int score);
	bool gameConditions(bool& playerDied) const;
	void handleEndGame(int score, bool finishedGame);
	void handleObjectCreation(int& condition, int world,
		bool& finishedGame, bool playerDied);
	void pause(bool& spacePressed, bool& paused, sf::Clock& clock);
	bool outOfTime(float timeRemained, bool& playerDied, int& life);

	bool m_startOver;
	Board m_board;
	GameWindow m_window;
};
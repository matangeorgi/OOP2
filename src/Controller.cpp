#include "Controller.h"

Controller::Controller() : m_startOver(true)
{
	TextureHolder::instance();
	AudioHolder::instance();

	std::fstream leaderBoard("leaderboard.txt", std::ios::app);
	if (!leaderBoard.is_open())
		throw std::exception("File couldn't open\n");
	leaderBoard.close();
}

//-----------------------------------------------------------------------------
void Controller::startMenu()
{
	m_startOver = true;
	while(m_window.isWindowOpen())
		switch (m_window.openMenu())
		{
		case START:		   startGame();		  break;
		case QUIT:		   exitGame();		  break;
		case LEADER_BOARD: openLeaderBoard(); break;
		}
}

//-----------------------------------------------------------------------------
void Controller :: startGame()
{
	sf::Clock clock;
	sf::Time deltaTime;
	float timeRemained;
	bool playerDied = false,
		finishedGame = false,
		paused = false,
		spacePressed = true;

	int	world = 1,
		score = 0,
		coins = 0,
		originalScore,
		originalCoins,
		life = START_LIFE,
		condition = 0;

	while(m_window.isWindowOpen() && life > 0)	// The game Loop
	{
		handleObjectCreation(condition, world, finishedGame, playerDied);

		if (finishedGame)
			break;

		m_startOver = false;
		timeRemained = STAGE_TIME;
		originalScore = score;
		originalCoins = coins;
		m_board.createPlayer(life, coins, score, condition);
		m_window.setBGStage(world);
		playerDied = false;

		while (gameConditions(playerDied))		// The Stage Loop
		{
			deltaTime = clock.restart();
			if (!paused)
			{
				m_board.moveObject(deltaTime);
				timeRemained -= deltaTime.asSeconds();
			}

			m_board.getGameData(score, coins, life);
			m_window.buildMap(m_board, 0, m_board.WindowLeftBorder());	// Drawing all the objects
			m_window.printText(m_board.WindowLeftBorder(), score, coins, world, (int)timeRemained, life);
			pause(spacePressed, paused, clock);

			if (outOfTime(timeRemained, playerDied, life))
				break;
			if (m_window.isExitPressed())
				return;
		}

		if (!playerDied)	// In case the user cleared the stage.
		{
			m_window.messageScreen("STAGE CLEARED",SLEEP);
			score += (int)timeRemained;
			world++;
		}
		else               // In case the user lost the stage.
		{
			score = originalScore;
			coins = originalCoins;
		}
	}

	handleEndGame(score, finishedGame);
	startMenu();
}

//-----------------------------------------------------------------------------
void Controller::handleLeaderBoard(int score)
{
	std::fstream leaderBoard("leaderboard.txt", std::ios::app);
	if (!leaderBoard.is_open())
		throw std::exception("File couldn't open\n");

	leaderBoard << score << std::endl;
	leaderBoard.close();
}

//-----------------------------------------------------------------------------
void Controller::handleEndGame(int score, bool finishedGame)
{
	AudioHolder::instance().stopBGSound();
	if (finishedGame)
	{
		AudioHolder::instance().playSound(AUDIO_WON);
		m_window.messageScreen("YOU WON, YOUR SCORE IS: " + std::to_string(score), SLEEP);
	}

	else
	{
		AudioHolder::instance().playSound(AUDIO_LOST);
		m_window.messageScreen("YOU LOST, YOUR SCORE IS: " + std::to_string(score), SLEEP);
	}
	handleLeaderBoard(score);
}

//-----------------------------------------------------------------------------
bool Controller::outOfTime(float timeRemained, bool& playerDied, int& life)
{
	if (timeRemained < 0)
	{
		playerDied = true;
		life--;
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// This function is used to pause the game
void Controller::pause(bool& spacePressed, bool& paused, sf::Clock& clock)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		spacePressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !spacePressed)
	{
		spacePressed = true;
		paused = !paused;
		AudioHolder::instance().playSound(AUDIO_PAUSE);
		clock.restart();

		if (paused)
			AudioHolder::instance().stopBGSound();
		else
			AudioHolder::instance().playSound(AUDIO_BACKGROUND);
	}
}

//-----------------------------------------------------------------------------
bool Controller::gameConditions(bool & playerDied) const
{
	return ((m_window.isWindowOpen() &&
		!(playerDied = m_board.isPlayerDead())) &&
		!m_board.isStageCleared());
}

//-----------------------------------------------------------------------------
void Controller::handleObjectCreation(int &condition,int world,
									  bool &finishedGame, bool playerDied)
{
	condition = m_board.restartStage();
	if (m_startOver)
		condition = 0;

	if ((world == 1 && !playerDied) || m_board.isStageCleared())
		finishedGame = m_board.readMap(m_startOver);
	else
		m_board.createObjects();

	AudioHolder::instance().playSound(AUDIO_BACKGROUND);
}

//-----------------------------------------------------------------------------
void Controller :: exitGame()
{
	m_window.finishScreen();
}

//-----------------------------------------------------------------------------
void Controller ::openLeaderBoard()
{
	m_window.leaderBoard();
	startMenu();
}

//-----------------------------------------------------------------------------
Controller::~Controller()
{
}

#include "GameWindow.h"

GameWindow::GameWindow() :
	m_window(sf::VideoMode(WIDTH,HEIGHT), "Super Mario Bros. 1",sf::Style::Close)
{
	sf::Vector2i windowPos ((sf::VideoMode::getDesktopMode().width / 2 - m_window.getSize().x / 2),
							(sf::VideoMode::getDesktopMode().height / 2 - m_window.getSize().y / 2 - WINDOW_GAP));
	m_window.setPosition(windowPos);
	initializeText();
	initializeScore();
}

//-----------------------------------------------------------------------------
int GameWindow::openMenu()
{
	m_window.setView(m_window.getDefaultView());	// getting the view back to normal
	m_window.clear();
	m_background.setTexture(TextureHolder::instance().getScreen(I_MENU_SCREEN));
	m_window.draw(m_background);

	for (const auto text : m_menuText)
		m_window.draw(text);

	m_window.display();

	return runMenu();
}

//-----------------------------------------------------------------------------
void GameWindow::buildMap(const Board& board, int timeRemained, float leftBorder)
{
	int index_moving = 0, index_static = 0;
	bool moving = true, statics = true, firePoles = true, firstTime = true;
	sf::Sprite temp;

	m_window.clear();
	m_window.draw(m_background);

	// Printing the sprites until we have finished the moving and statics.
	while (moving || statics || firePoles)
	{
		temp = board.drawToWindow(index_moving, index_static, moving, statics, firePoles);
		m_window.draw(temp);

		if (!moving && firstTime)
		{
			index_moving = 0;
			firstTime = false;
		}
	}
	
	// Fixing the view by the player direction
	sf::View view = sf::View(sf::FloatRect(leftBorder, 0, VIEW_WIDTH, VIEW_HEIGHT));
	m_window.setView(view);
}

//-----------------------------------------------------------------------------
void GameWindow::printText(float leftBorder, int score, int coins, int world, int time, int life)
{
	m_message[SCORE].setPosition(SCORES_X + leftBorder, GAME_Y);
	m_message[SCORE].setString("SCORE: " + std::to_string(score));

	m_message[COINS].setPosition(COINS_X + leftBorder, GAME_Y);
	m_message[COINS].setString("COINS: " + std::to_string(coins));

	m_message[WORLD].setPosition(WORLD_X + leftBorder, GAME_Y);
	m_message[WORLD].setString("WORLD: " + std::to_string(world));

	m_message[TIME].setPosition(TIME_X + leftBorder, GAME_Y);
	m_message[TIME].setString("TIME: " + std::to_string(time));

	m_message[LIFE].setPosition(LIFE_X + leftBorder, GAME_Y);
	m_message[LIFE].setString("LIFE: " + std::to_string(life));

	for (auto message : m_message)
		m_window.draw(message);

	m_window.display();
}

//-----------------------------------------------------------------------------
// Setting the background image based on stage.
void GameWindow:: setBGStage(const int stage)
{
	m_background.setTexture(TextureHolder::instance().getLevel(stage-1));

	sf::View view = sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT));
	m_window.setView(view);
}

//-----------------------------------------------------------------------------
int GameWindow::runMenu()
{
	int action = NONE;
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::MouseButtonReleased:
				action = buttonPressed(event);

				if (action != NONE)
					return action;
			}
		}
	}
	return QUIT;
}

//-----------------------------------------------------------------------------
int GameWindow::buttonPressed(sf::Event event) const
{
	auto location = m_window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });

	if (m_menuText[START].getGlobalBounds().contains(location))
		return START;

	if (m_menuText[QUIT].getGlobalBounds().contains(location))
		return QUIT;

	if (m_menuText[LEADER_BOARD].getGlobalBounds().contains(location))
		return LEADER_BOARD;

	if (m_leaderText[LEADERS-1].getGlobalBounds().contains(location))
		return BACK;

	return NONE;
}

//-----------------------------------------------------------------------------
void GameWindow::initializeText()
{
	m_font.loadFromFile("Fixedsys500c.ttf");
	
	for (auto& message : m_menuText)
	{
		message.setFont(m_font);
		message.setColor(sf::Color::White);
		message.setOutlineColor(sf::Color::Black);
		message.setOutlineThickness(THICKNESS);
		message.setCharacterSize(FONT_SIZE);
	}

	for (auto& message : m_message)
	{
		message.setFont(m_font);
		message.setColor(sf::Color::White);
		message.setCharacterSize(GAME_FONT_SIZE);
	}

	initializeMenuText();
}

//-----------------------------------------------------------------------------
void GameWindow::initializeMenuText()
{
	m_menuText[START].setString("START GAME");
	m_menuText[START].setPosition(START_X, START_Y);

	m_menuText[LEADER_BOARD].setString("SCORE");
	m_menuText[LEADER_BOARD].setPosition(SCORE_X, SCORE_Y);

	m_menuText[QUIT].setString("EXIT");
	m_menuText[QUIT].setPosition(EXIT_X, EXIT_Y);

	m_finishText.setFont(m_font);
	m_finishText.setColor(sf::Color::White);
	m_finishText.setCharacterSize(FONT_SIZE);
	m_finishText.setPosition(EXIT_X, EXIT_Y);
}

//-----------------------------------------------------------------------------
void GameWindow::finishScreen()
{
	messageScreen("BYE BYE!",EXIT_SLEEP);
	m_window.close();
}

//-----------------------------------------------------------------------------
bool GameWindow::isExitPressed()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			finishScreen();
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
void GameWindow::messageScreen(std::string message, int sleep)
{
	m_window.clear();
	m_window.setView(m_window.getDefaultView());
	m_background.setTexture(TextureHolder::instance().getScreen(I_QUIT_SCREEN));
	m_finishText.setString(message);
	m_window.draw(m_background);
	m_window.draw(m_finishText);
	m_window.display();

	std::this_thread::sleep_for(std::chrono::seconds(sleep));  // Freezing the screen
	m_background.setScale(1, 1);
}

//-----------------------------------------------------------------------------
// This function handles the leaderBoard
void GameWindow::leaderBoard()
{
	m_window.clear();
	readFromFile();	// Reading the scores from file
	m_background.setTexture(TextureHolder::instance().getScreen(I_LEADERBOARD_SCREEN));
	m_background.setScale(1, 1);
	m_window.draw(m_background);

	for (int i = 0; i < LEADERS -1 && i < m_leaderVec.size(); i++)
	{
		m_leaderText[i].setFont(m_font);
		m_leaderText[i].setColor(sf::Color::White);
		m_leaderText[i].setCharacterSize(FONT_SIZE);
		m_leaderText[i].setString(std::to_string(i + 1) + ". " + std::to_string(m_leaderVec[i]));
		m_window.draw(m_leaderText[i]);
	}

	m_window.draw(m_leaderText[LEADERS - 1]);
	m_window.display();
	runMenu();
}

//-----------------------------------------------------------------------------
void GameWindow::initializeScore()
{
	for (int i = 0; i < LEADERS; i++)
	{
		m_leaderText[i].setFont(m_font);
		m_leaderText[i].setColor(sf::Color::White);
		m_leaderText[i].setCharacterSize(FONT_SIZE);
		m_leaderText[i].setPosition(LEADER_X, LEADER_Y + i * LEADER_GAP);

		if (i == LEADERS - 1)
		{
			m_leaderText[i].setString("BACK");
			m_leaderText[i].setPosition(10, 10);
		}
	}
}

//-----------------------------------------------------------------------------
void GameWindow::readFromFile()
{
	std::fstream leaderBoard("leaderboard.txt");
	if (!leaderBoard.is_open())
		throw std::exception("File couldn't open\n");

	m_leaderVec.clear();
	auto line = std::string();
	while (leaderBoard.peek() != NONE)
	{
		std::getline(leaderBoard, line);
		m_leaderVec.push_back(std::stoi(line));
	}
	leaderBoard.close();
	std::sort(m_leaderVec.begin(), m_leaderVec.end(), std::greater<int>());
}

//-----------------------------------------------------------------------------
bool GameWindow::isWindowOpen() const
{
	return (m_window.isOpen());
}

//-----------------------------------------------------------------------------
void GameWindow::closeWindow()
{
	m_window.close();
}

//-----------------------------------------------------------------------------
GameWindow::~GameWindow()
{
}

#pragma once

#include <thread>
#include <chrono>
#include <array>

#include "TextureHolder.h"
#include "AudioHolder.h"
#include "Board.h"

class GameWindow
{
public:
	GameWindow();

	void closeWindow();
	int openMenu();
	void leaderBoard();
	void finishScreen();
	bool isExitPressed();
	bool isWindowOpen() const;
	void setBGStage(const int stage);
	void messageScreen(std::string message, int sleep);
	void buildMap(const Board& board, int timeRemained, float leftBorder);
	void printText(float leftBorder, int score, int coins, int world, int time, int life);
	~GameWindow();

private:

	int runMenu();
	void readFromFile();
	void initializeText();
	void initializeScore();
	void initializeMenuText();
	int buttonPressed(sf::Event event)const;

	sf::Font m_font;
	sf::Text m_finishText;
	sf::Sprite m_background;
	sf::RenderWindow m_window;
	std::vector<int> m_leaderVec;
	std::array<sf::Text, MESSAGES> m_message;
	std::array<sf::Text, MENU_MESSAGES> m_menuText;
	std::array<sf::Text, LEADERS> m_leaderText;
};
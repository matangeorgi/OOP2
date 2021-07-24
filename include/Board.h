#pragma once

#include <fstream>
#include <string>
#include <array>

#include "MovingObject.h"
#include "StaticObject.h"
#include "Collision.h"

class Board
{
public:
	Board();

	int restartStage();
	void createObjects();
	bool isPlayerDead() const;
	bool readMap(bool restart);
	bool isStageCleared() const;
	float WindowLeftBorder() const;
	void moveObject(sf::Time deltaTime);
	void createPlayer(int life, int coins, int score,int condition);
	void getGameData(int& score, int& coins, int& life);
	const sf::Sprite& drawToWindow(int& index_moving, int& index_static,
								   bool& moving, bool& statics, bool& firePoles) const;

	~Board();
private:

	void shootFireWorks();
	int marioState() const;
	void tryMove(int index, sf::Time deltaTime);
	void checkCollision(std::unique_ptr<MovingObject> &object);
	void buildObject(int row, int col, char element);
	bool tryToDelete(GameObject* Obj);

	bool m_releasedShift;
	Collision m_collision;
	Player* m_player;
	std::ifstream m_inputFile;
	std::array <std::string, ROWS> m_map;
	std::vector<std::unique_ptr<StaticObject>> m_static;
	std::vector<std::unique_ptr<MovingObject>> m_moving;
};

static std::unique_ptr<MovingObject> createMovingObj(int row, int col, char element);
static std::unique_ptr<StaticObject> createStaticObj(int row, int col, char element);
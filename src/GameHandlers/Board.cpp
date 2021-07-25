#include "Board.h"

Board::Board() : m_player(nullptr), m_releasedShift(true)
{
	m_inputFile.open("Levels.txt");
	if(!m_inputFile.is_open())
		throw std::exception("maps file couldn't be open.\n");
}

//-----------------------------------------------------------------------------
void Board::moveObject(sf::Time deltaTime)
{
	shootFireWorks();							// In case we are shooting fireworks
	for (int i = 0; i < m_moving.size(); i++)
	{
		if (m_moving[i]->isShouldMove())		// Explained in README
			tryMove(i, deltaTime);				// Moving the objects and check collisions

		if (tryToDelete(m_moving[i].get()) && i != m_moving.size() - 1) // Checking if there is no longer use for an object.
		{
			m_player->addPoints(m_moving[i]->getGatheredPoints());		// In case we got points indirectly here we pick them.

			if (m_moving[i]->getGatheredPoints() == COIN_POINTS)		// In case we got Coins indirectly here we pick them.
				m_player->addCoin();

			m_moving[i].release();
			m_moving.erase(m_moving.begin() + i--);
		}
	}

	for (int i = 0; i < m_static.size(); i++)
		if (tryToDelete(m_static[i].get()))								// Checking if there is no longer use for an object.
		{
			m_static[i].release();
			m_static.erase(m_static.begin() + i--);
		}
}

//-----------------------------------------------------------------------------
// This function is called to try and shoot a firework if the player is
// fiery Mario and pressed shift.
void Board::shootFireWorks()
{
	// In this function we ask if shift is released so we wont spam fireworks.

	if (m_player->isFiery() && m_releasedShift &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		m_releasedShift = false;
		AudioHolder::instance().playSound(AUDIO_FIRE);
		m_moving.emplace(m_moving.begin(), std::make_unique<Fireworks>(m_player->getPos(), m_player->getDirection()));
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		m_releasedShift = true;
}

//-----------------------------------------------------------------------------
// The main function that handles movement.
void Board::tryMove(int index, sf::Time deltaTime)
{
	// Checking if the moving object is in the view, if it isn't we shouldn't move him.
	if (m_moving[index]->getPos().x >= m_player->getLeftBorder() - ICON_SIZE &&
		m_moving[index]->getPos().x < m_player->getLeftBorder() + VIEW_WIDTH)
	{
		m_moving[index]->move(deltaTime);
		m_moving[index]->setToAir();

		if (index == m_moving.size() - 1 && m_player->isDead())
			return;

		checkCollision(m_moving[index]);
	}
}

//-----------------------------------------------------------------------------
// In case the object is no longer on the screen forever, or his delete
// flag is up - we return true to delete him.
bool Board::tryToDelete(GameObject* Obj)
{
	if (Obj->isDelete() ||
		Obj->getPos().x < m_player->getLeftBorder() - (ICON_SIZE * 2) ||
		Obj->getPos().y > VIEW_HEIGHT + ICON_SIZE * 2)
		return true;
	return false;
}

//-----------------------------------------------------------------------------
// Here a moving object check collision with static and moving object
void Board::checkCollision(std::unique_ptr<MovingObject>& object)
{
	for (auto& moving : m_moving)		// Checking collisions with static
		if (object != moving)
			if (object->draw().getGlobalBounds().intersects(moving->draw().getGlobalBounds()))
				m_collision.processMovCollision(*object, *moving);

	for (auto& staticObj : m_static)	// Checking collisions with moving
		if (object->draw().getGlobalBounds().intersects(staticObj->draw().getGlobalBounds()))
			m_collision.processStaticCollision(*object, *staticObj);
}

//-----------------------------------------------------------------------------
bool Board::readMap(bool restart)
{
	if (restart)					// In case we started a new game
		m_inputFile.seekg(0);

	if (m_inputFile.eof())			// If we finished all maps
		return true;

	auto line = std::string();
	for (int i = 0; i < ROWS; i++)
	{
		m_map[i].clear();
		std::getline(m_inputFile, line);
		m_map[i] = line;
	}

	if(m_map.size() != ROWS)
		throw std::exception("Map size isn't correct.\n");

	createObjects();				// Creating all the objects.
	return false;
}

//-----------------------------------------------------------------------------
// This function is used to send the sprite to print the map from GameWindow class.
// The function sends specific sprite by the boolean that was sent.
const sf::Sprite& Board::drawToWindow(int& index_moving, int& index_static,
	bool& moving, bool& statics, bool& firePoles) const
{
	sf::Sprite temp;

	// sending the specific sprite - moving object by the index given.
	if (moving)
	{
		if (m_moving.size() - 1 == index_moving)
			moving = false;
		else if (!m_moving[index_moving]->isFirePole())
			return m_moving[index_moving++]->draw();
		else
			index_moving++;
	}

	// sending the specific sprite - static object by the index given.
	else if (statics)
	{
		if (m_static.size() == index_static)
			statics = false;
		else
			return m_static[index_static++]->draw();
	}
	else
	{
		if (m_moving.size() == index_moving)
			firePoles = false;
		else if (m_moving[index_moving]->isFirePole() || index_moving == m_moving.size() - 1)
			return m_moving[index_moving++]->draw();
		else
			index_moving++;
	}
	return temp;
}

//-----------------------------------------------------------------------------
void Board::createObjects()
{
	for (int row = 0; row < ROWS; row++)
		for (int col = 0; col < m_map[row].size(); col++)
			if (m_map[row][col] != AIR)
				buildObject(row, col, m_map[row][col]);
}

//-----------------------------------------------------------------------------
void Board::buildObject(int row, int col, char element)
{
	std::unique_ptr<MovingObject> movable;
	std::unique_ptr<StaticObject> unmovable;

	movable = createMovingObj(row, col, element);

	if (movable)
	{
		m_moving.push_back(std::move(movable));
		return;
	}

	unmovable = createStaticObj(row, col, element);
	if (unmovable)
	{
		m_static.push_back(std::move(unmovable));
		return;
	}

	throw std::exception("No such element was declared.\n");
}

//-----------------------------------------------------------------------------
static std::unique_ptr<MovingObject> createMovingObj(int row, int col, char element)
{
	switch (element)
	{
	case PLATFORM: return std::make_unique<Platforms>(row, col);
	case TORTOISE:return std::make_unique<Tortoise>(row, col);
	case FLYING_TORTOISE:return std::make_unique<FlyingTortoise>(row, col);
	case BAD_MUSHROOM:return std::make_unique<BadMushroom>(row, col);
	case PIRANA_PLANT:return std::make_unique<PiranaPlants>(row, col);
	case SUPER_MUSH:return std::make_unique<SuperMushroom>(row, col);
	case FIRE_BALL:return std::make_unique<FireBall>(row, col);
	case FIRE_POLE:return std::make_unique<FirePole>(row, col);
	case BRICK:return std::make_unique<Brick>(row, col);
	case COIN: return std::make_unique<Coin>(row, col);
	case QUESTION:return std::make_unique<QuestionBlock>(row, col);
	case GOAL_FLAG:return std::make_unique<GoalFlag>(row, col);
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
static std::unique_ptr<StaticObject> createStaticObj(int row, int col, char element)
{
	switch (element)
	{
	case FLOOR:return std::make_unique<Floor>(row, col);
	case PIPE:return std::make_unique<Pipe>(row, col);
	case BLOCK:return std::make_unique<Block>(row, col);
	case GOAL_POLE:return std::make_unique<GoalPole>(row, col);
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
// This function create the player object
void Board::createPlayer(int life,int coins, int score, int condition)
{
	m_moving.push_back(std::make_unique<Player>(life,score,coins,condition));

	if (auto p = dynamic_cast<Player*>(m_moving[m_moving.size() - 1].get()))
		m_player = p;
}

//-----------------------------------------------------------------------------
// restarting the stage in case the player have died.
int Board::restartStage()
{
	int condition = 0;
	condition = marioState();

	for (int i = 0; i < m_moving.size(); i++)
	{
		m_moving[i].release();
		m_moving.erase(m_moving.begin() + i--);
	}
	for (int i = 0; i < m_static.size(); i++)
	{
		m_static[i].release();
		m_static.erase(m_static.begin() + i--);
	}

	return condition;
}

//-----------------------------------------------------------------------------
int Board::marioState() const
{
	if (m_player)
	{
		if (m_player->isFiery())
			return I_F_MARIO;
		else if (m_player->isFieryOrSuper())
			return I_S_MARIO;
		return I_MARIO;
	}
}

//-----------------------------------------------------------------------------
void Board::getGameData(int& score, int& coins, int& life)
{
	score = m_player->getPoints();
	coins = m_player->getCoins();
	life = m_player->getLife();
}

//-----------------------------------------------------------------------------
float Board::WindowLeftBorder() const
{
	return m_player->getLeftBorder();
}

//-----------------------------------------------------------------------------
bool Board::isStageCleared() const
{
	return m_player->isStageCleared();
}

//-----------------------------------------------------------------------------
bool Board::isPlayerDead() const
{
	if (m_player && m_player->isDelete())
		return true;
	return false;
}

//-----------------------------------------------------------------------------
Board::~Board()
{
}

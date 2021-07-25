#include "TextureHolder.h"

TextureHolder::TextureHolder()
{
	m_texture.push_back(std::vector<sf::Texture>());
	uploadFiles();
}

void TextureHolder::uploadFiles()
{
	sf::Texture temp;

	uploadPlayer(temp);
	uploadEnemy(temp);
	uploadWall(temp);
	uploadCoin(temp);
	uploadGoalFlag(temp);
	uploadMenu(temp);
	uploadLevels(temp);
	uploadObstacles(temp);
	uploadStatic(temp);
	uploadGoodObj(temp);
	uploadFireworks(temp);
}

void TextureHolder::uploadPlayer(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("Mario.png");
	m_texture[I_PLAYER].push_back(temp);

	temp.loadFromFile("SuperMario.png");
	m_texture[I_PLAYER].push_back(temp);

	temp.loadFromFile("FieryMario.png");
	m_texture[I_PLAYER].push_back(temp);
}

void TextureHolder::uploadEnemy(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("BadMushroom.png");
	m_texture[I_ENEMY].push_back(temp);

	temp.loadFromFile("Tortoise.png");
	m_texture[I_ENEMY].push_back(temp);

	temp.loadFromFile("FlyingTortoise.png");
	m_texture[I_ENEMY].push_back(temp);

	temp.loadFromFile("PiranaPlant.png");
	m_texture[I_ENEMY].push_back(temp);
}

void TextureHolder::uploadWall(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("Floor.png");
	m_texture[I_WALL].push_back(temp);

	temp.loadFromFile("Bricks.png");
	m_texture[I_WALL].push_back(temp);

	temp.loadFromFile("Block.png");
	m_texture[I_WALL].push_back(temp);

	temp.loadFromFile("QuestionBlock.png");
	m_texture[I_WALL].push_back(temp);
}

void TextureHolder::uploadCoin(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("Coin.png");
	m_texture[I_COIN].push_back(temp);
}

void TextureHolder::uploadGoalFlag(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("GoalPole.png");
	m_texture[I_GOAL_FLAG].push_back(temp);

	temp.loadFromFile("Flag.png");
	m_texture[I_GOAL_FLAG].push_back(temp);
}

void TextureHolder::uploadMenu(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("Menu.jpg");
	m_texture[I_MENU].push_back(temp);

	temp.loadFromFile("quitScreen.jpg");
	m_texture[I_MENU].push_back(temp);

	temp.loadFromFile("leaderBoard.jpg");
	m_texture[I_MENU].push_back(temp);

}

void TextureHolder::uploadLevels(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("level_1.png");
	m_texture[I_LEVELS].push_back(temp);

	temp.loadFromFile("level_2.png");
	m_texture[I_LEVELS].push_back(temp);

	temp.loadFromFile("level_3.png");
	m_texture[I_LEVELS].push_back(temp);

	temp.loadFromFile("level_4.png");
	m_texture[I_LEVELS].push_back(temp);
}

void TextureHolder::uploadObstacles(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("FireBall.png");
	m_texture[I_OBSTACLES].push_back(temp);

	temp.loadFromFile("FirePole.png");
	m_texture[I_OBSTACLES].push_back(temp);
}

void TextureHolder::uploadStatic(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("Pipe.png");
	m_texture[I_STATIC].push_back(temp);

	temp.loadFromFile("Platform.png");
	m_texture[I_STATIC].push_back(temp);
}

void TextureHolder::uploadGoodObj(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("SuperMushroom.png");
	m_texture[I_GOOD_OBJ].push_back(temp);

	temp.loadFromFile("FireFlower.png");
	m_texture[I_GOOD_OBJ].push_back(temp);
}

void TextureHolder::uploadFireworks(sf::Texture temp)
{
	m_texture.push_back(std::vector<sf::Texture>());
	temp.loadFromFile("Fireworks.png");
	m_texture[I_FIREWORKS].push_back(temp);
}

//-----------------------------------------------------------------------------
// This function is used to return the correct texture by the element given as input.
const sf::Texture& TextureHolder::getTextures(char element) const
{
	switch (element)
	{
	case QUESTION:	  return m_texture[I_WALL][I_QUESTION];
	case BLOCK:		  return m_texture[I_WALL][I_BLOCK];
	case BRICK:		  return m_texture[I_WALL][I_BRICK];
	case FLOOR:		  return m_texture[I_WALL][I_FLOOR];
	case COIN:		  return m_texture[I_COIN][0];
	case PLATFORM:	  return m_texture[I_STATIC][I_PLATFORM];
	case PIPE:		  return m_texture[I_STATIC][I_PIPE];
	case FIRE_BALL:   return m_texture[I_OBSTACLES][I_FIREBALL];
	case FIRE_POLE:   return m_texture[I_OBSTACLES][I_FIREPOLE];
	case SUPER_MUSH:  return m_texture[I_GOOD_OBJ][I_SUPER_MUSH];
	case FIRE_FLOWER: return m_texture[I_GOOD_OBJ][I_FIRE_FLOWER];
	case FIREWORKS:   return m_texture[I_FIREWORKS][0];
	}
	return sf::Texture();
}

//-----------------------------------------------------------------------------
const sf::Texture& TextureHolder::getLevel(int level) const
{
	return m_texture[I_LEVELS][level];
}

//-----------------------------------------------------------------------------
const sf::Texture& TextureHolder::getScreen(int screen) const
{
	return m_texture[I_MENU][screen];
}

//-----------------------------------------------------------------------------
const sf::Texture& TextureHolder::getPlayer(int mode) const
{
	return m_texture[I_PLAYER][mode];
}

//-----------------------------------------------------------------------------
const sf::Texture& TextureHolder::getFlag(int kind) const
{
	return m_texture[I_GOAL_FLAG][kind];
}
//-----------------------------------------------------------------------------
const sf::Texture& TextureHolder::getEnemy(int kind) const
{
	return m_texture[I_ENEMY][kind];
}
//-----------------------------------------------------------------------------
TextureHolder& TextureHolder::instance()
{
	static TextureHolder instance;
	return instance;
}

//-----------------------------------------------------------------------------
TextureHolder::~TextureHolder()
{
}



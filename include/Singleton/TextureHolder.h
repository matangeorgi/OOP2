#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Macros.h"

// This is a singleton class.
class TextureHolder
{
public:
	static TextureHolder& instance();
	const sf::Texture& getTextures(char element) const;
	const sf::Texture& getLevel(int level) const;
	const sf::Texture& getPlayer(int mode) const;
	const sf::Texture& getEnemy(int kind) const;
	const sf::Texture& getScreen(int screen) const;
	const sf::Texture& getFlag(int kind) const;
	~TextureHolder();

private:
	TextureHolder();
	TextureHolder(const TextureHolder&) = default;
	TextureHolder& operator=(const TextureHolder&) = default;

	void uploadFiles();

	void uploadPlayer(sf::Texture temp);
	void uploadEnemy(sf::Texture temp);
	void uploadGoalFlag(sf::Texture temp);
	void uploadCoin(sf::Texture temp);
	void uploadWall(sf::Texture temp);
	void uploadObstacles(sf::Texture temp);
	void uploadLevels(sf::Texture temp);
	void uploadMenu(sf::Texture temp);
	void uploadStatic(sf::Texture temp);
	void uploadGoodObj(sf::Texture temp);
	void uploadFireworks(sf::Texture temp);

	std::vector<std::vector<sf::Texture>> m_texture;

};
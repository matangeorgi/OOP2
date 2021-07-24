#pragma once

#include "Macros.h"
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(const sf::Texture& data, bool dir, sf::Sprite& sprite, int size);
    
    void setDeadSprite();
    void setDirection(bool Direction);
    void initializeTexture(int size);
    void pullingFlag(sf::Time deltaTime);
    void changeMarioTexture(const sf::Texture& data, int size);
    void staticShift(sf::Time deltaTime, float switchTime);
    void updatePlayer(bool direction, bool standing, bool fire,
                      bool inAir, bool duck, float velocity, sf::Time deltaTime);

    ~Animation();

private:
    void duckFunc();
    void fireFunc();
    void standFunc();

    bool m_dir;
    sf::Sprite& m_sprite;
    sf::IntRect m_uvRect;
    sf::Texture m_data;
    
    int m_size,
        m_current;
    float m_totalTime;
};

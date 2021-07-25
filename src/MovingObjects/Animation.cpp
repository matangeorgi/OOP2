#include "Animation.h"

Animation::Animation(const sf::Texture& data, bool dir, sf::Sprite& sprite, int size)
    : m_data(data), m_dir(dir), m_sprite(sprite),m_size(size), m_totalTime(0),m_current(0)
{
    initializeTexture(size);
    m_sprite.setTexture(data);
}

//-----------------------------------------------------------------------------
// This function is used to shift between the different sprites that
// an object have.
void Animation::staticShift(sf::Time deltaTime, float switchTime)
{
    m_totalTime += deltaTime.asSeconds();               // Counting the time passed into a member.
    if (m_totalTime > switchTime)                       // Inc case the time is larger then SwitchTime
    {                                                   // We change the sprite.
        m_totalTime -= switchTime;
        m_current++;
        if (m_current >= m_size - 1)
            m_current = 0;

        m_uvRect.left = m_uvRect.width * m_current;     // Here we decide which sprite we will take.
       m_sprite.setTextureRect(m_uvRect);
    }
}

//-----------------------------------------------------------------------------
// This function flips the sprite to change direction he posing to.
void Animation::setDirection(bool Direction)
{
    if (Direction)
    {
        m_uvRect.left = m_current * m_uvRect.width;
        m_uvRect.width = std::abs(m_uvRect.width);
    }
    else
    {
        m_uvRect.left = (m_current+1) * std::abs(m_uvRect.width);
        m_uvRect.width = -std::abs(m_uvRect.width);
    }
    m_sprite.setTextureRect(m_uvRect);
}

//-----------------------------------------------------------------------------
void Animation::initializeTexture(int size)
{
    m_size = size;
    m_uvRect.width = (m_data.getSize().x) / m_size;
    m_uvRect.height = m_data.getSize().y;
    m_sprite.setTextureRect(m_uvRect);
}

//-----------------------------------------------------------------------------
void Animation::changeMarioTexture(const sf::Texture& data, int size)
{
    m_data = data;
    m_sprite.setTexture(data);
    initializeTexture(size);
}

//-----------------------------------------------------------------------------
// This function only handles the player sprite.
void Animation::updatePlayer(bool direction,bool standing, bool fire,
                             bool inAir, bool duck, float velocity, sf::Time deltaTime)
{
    if (fire)               // Player shoots
    {
        fireFunc();
        return;
    }
    if (duck)               // Player Ducking
    {
        duckFunc();
        return;
    }
    if (standing && !inAir) // Player Standing
    {
        standFunc();
        return;
    }

    m_totalTime += deltaTime.asSeconds();

    if (inAir)              // Player Jumping
        m_current = PLAYER_JUMP;


    // Player slipping
    else if (direction == LEFT && velocity > 0 ||
        direction == RIGHT && velocity < 0)
        m_current = PLAYER_SLIP;
       
    // Player Walking
    else if (m_totalTime > SWITCH)
    {
        m_totalTime -= SWITCH;
        m_current++;

        if (m_current > PLAYER_WALK_END)
            m_current = PLAYER_WALK_FIRST;
    }

    m_uvRect.left = m_uvRect.width * m_current;
    m_sprite.setTextureRect(m_uvRect);
}

//-----------------------------------------------------------------------------
void Animation::duckFunc()
{
    m_current = PLAYER_D;
    m_uvRect.height /= 2;
    m_uvRect.left = m_uvRect.width * m_current;
    m_sprite.setTextureRect(m_uvRect);
    m_uvRect.height *= 2;
}

//-----------------------------------------------------------------------------
void Animation::fireFunc()
{
    m_current = PLAYER_FIRE;
    m_uvRect.left = m_uvRect.width * m_current;
    m_sprite.setTextureRect(m_uvRect);
}

//-----------------------------------------------------------------------------
void Animation::standFunc()
{
    m_current = PLAYER_STAND;
    m_uvRect.left = m_uvRect.width * m_current;
    m_sprite.setTextureRect(m_uvRect);
}

//-----------------------------------------------------------------------------
void Animation::setDeadSprite()
{
    setDirection(LEFT);
    m_uvRect.left = std::abs(m_uvRect.width) * m_size;
    m_sprite.setTextureRect(m_uvRect);
}

//-----------------------------------------------------------------------------
// This function Handle the animation of a flag going down.
void Animation::pullingFlag(sf::Time deltaTime)
{
    m_totalTime += deltaTime.asSeconds();
    if (m_totalTime > SWITCH)
    {
        m_totalTime -= SWITCH;
        m_current++;
        if (m_current > PULLING_PIC+1)
            m_current = PULLING_PIC;

        m_uvRect.left = m_uvRect.width * m_current;
        m_sprite.setTextureRect(m_uvRect);
    }
}

//-----------------------------------------------------------------------------
Animation::~Animation()
{
}
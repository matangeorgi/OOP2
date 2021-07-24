#include "MovingObject.h"

MovingObject::MovingObject(const sf::Texture& data, bool dir, int size, int row, int col): m_gatheredPoints(0),
	 GameObject(row, col), m_animation(data, dir, m_sprite, size), m_dir(dir), m_dead(false), m_deathTimePassed(0)
	, m_directionChange(0), m_air(true), m_velocity(0,0), m_shouldMove(true), m_tortoiseKill(false)
{
}

//-----------------------------------------------------------------------------
// This function is being used for tortoise and BadMushroom
void MovingObject::sideMove(sf::Time deltaTime, float speed)
{
	if (m_sprite.getPosition().y > m_lastPos.y)
	{
		m_lastPos = m_sprite.getPosition();
		return;
	}

	m_velocity = sf::Vector2f(0, 0);
	m_directionChange += deltaTime.asSeconds();

	switch (m_dir)
	{
	case RIGHT:
		goRight();
		break;

	case LEFT:
		goLeft();
		break;
	}

	if (m_air)
		m_velocity.y = TOP_FALL_SPEED * deltaTime.asSeconds();

	m_velocity.x *= speed * deltaTime.asSeconds();
	m_sprite.move(m_velocity);

	m_lastPos = m_sprite.getPosition();
}

//-----------------------------------------------------------------------------
// This function is used by flying tortoise and playform.
void MovingObject::upDownMove(sf::Time deltaTime, float speed, int top, int bottom, float switchTime)
{
	switch (m_dir)
	{
	case UP:
		goUp();
		break;

	case DOWN:
		goDown();
		break;
	}

	m_animation.staticShift(deltaTime, switchTime);
	m_velocity.y *= speed * deltaTime.asSeconds();
	m_sprite.move(m_velocity);

	// Switching directions
	if (m_sprite.getPosition().y > bottom)
		m_dir = UP;
	else if (m_sprite.getPosition().y < top)
		m_dir = DOWN;
}

//-----------------------------------------------------------------------------
void MovingObject::decideDirection()
{
	if (m_directionChange > CHANGE_DIR_TIME)
	{
		if (m_dir == RIGHT)
			m_dir = LEFT;
		else
			m_dir = RIGHT;

		m_directionChange = 0;
	}
}

//-----------------------------------------------------------------------------
// This function is used when totrtoise kiil an enemy,
// there is a different way to die.
void MovingObject::handleDeathTortoise(sf::Time deltaTime)
{
	if (m_deathTimePassed == 0)
	{
		m_velocity.y = BUMP;
		m_sprite.setRotation(FLIP);
	}

	m_deathTimePassed += deltaTime.asSeconds();

	if (m_deathTimePassed > SWITCH)
		fall(deltaTime);

	m_sprite.move(m_velocity);
}
//-----------------------------------------------------------------------------
// This function helps collect points within indirect kill
void MovingObject::setUniqueKill()
{
	m_tortoiseKill = true;
	m_dead = true;
	m_gatheredPoints = KILL_POINTS;
	AudioHolder::instance().playSound(AUDIO_KILL);
}

//-----------------------------------------------------------------------------
// The function pull the bricks down when being bumped, so as the coins
// and question block
void MovingObject::squareMove(sf::Time deltaTime)
{
	m_animation.staticShift(deltaTime, SWITCH);
	if (std::abs(getPos().y - m_lastPos.y) > BRICK_GAP)
	{
		m_velocity.y += deltaTime.asSeconds();
		if (m_velocity.y > TOP_FALL_SPEED * deltaTime.asSeconds())
			m_velocity.y = TOP_FALL_SPEED * deltaTime.asSeconds();

		m_sprite.move(m_velocity);
	}
	else if (m_velocity.y != 0)
	{
		m_velocity.y = 0;
		m_sprite.setPosition(m_lastPos);
		m_shouldMove = false;
	}
}

//-----------------------------------------------------------------------------
void MovingObject::fall(sf::Time deltaTime)
{
	m_velocity.y += FALLING_VEL * deltaTime.asSeconds();
	if (m_velocity.y > TOP_FALL_SPEED * deltaTime.asSeconds())
		m_velocity.y = TOP_FALL_SPEED * deltaTime.asSeconds();
}

//-----------------------------------------------------------------------------
void MovingObject::handleDeath(sf::Time deltaTime)
{
	m_deathTimePassed += deltaTime.asSeconds();		// Couting time before we delete the object
	if (m_deathTimePassed > DEATH_TIME)
		setDelete();
}

//-----------------------------------------------------------------------------
void MovingObject::squareBump()
{
	m_velocity.y = SQUARE_BUMP;
	m_sprite.move(m_velocity);
	m_shouldMove = true;
}
//-----------------------------------------------------------------------------
void MovingObject::elevate(const MovingObject& platform)
{
	if (m_velocity.y > 0)
		m_velocity.y = 0;
	m_sprite.move(platform.getDirectionVec());
}

//-----------------------------------------------------------------------------
void MovingObject::addGatheredPoints(int points)
{
	m_gatheredPoints = points;
}

//-----------------------------------------------------------------------------
void MovingObject::bump()
{
	m_velocity.y = BUMP;
}

//-----------------------------------------------------------------------------
int MovingObject::getGatheredPoints() const
{
	return m_gatheredPoints;
}

//-----------------------------------------------------------------------------
void MovingObject::setDirection(bool direction)
{
	m_dir = direction;
}

//-----------------------------------------------------------------------------
void MovingObject::setPreviousPos()
{
	m_sprite.setPosition(m_lastPos);
}

//-----------------------------------------------------------------------------
bool MovingObject::isShouldMove() const
{
	return m_shouldMove;
}

//-----------------------------------------------------------------------------
void MovingObject::setToAir()
{
	m_air = true;
}

//-----------------------------------------------------------------------------
void MovingObject::goDown()
{
	m_velocity.y++;
}

//-----------------------------------------------------------------------------
void MovingObject::goUp()
{
	m_velocity.y--;
}

//-----------------------------------------------------------------------------
void MovingObject::goRight()
{
	m_velocity.x++;
}

//-----------------------------------------------------------------------------
void MovingObject::goLeft()
{
	m_velocity.x--;
}

//-----------------------------------------------------------------------------
void MovingObject::kill()
{
	m_dead = true;
	m_animation.setDeadSprite();
}

//-----------------------------------------------------------------------------
void MovingObject::setGrounded()
{
	m_air = false;
}

//-----------------------------------------------------------------------------
bool MovingObject::isDead() const
{
	return m_dead;
}

//-----------------------------------------------------------------------------
sf::Vector2f MovingObject::getDirectionVec() const
{
	return m_velocity;
}

//-----------------------------------------------------------------------------
void MovingObject::move(sf::Time deltaTime)
{
}
//-----------------------------------------------------------------------------
MovingObject::~MovingObject()
{
}






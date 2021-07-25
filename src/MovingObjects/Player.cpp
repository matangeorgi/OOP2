#include "Player.h"

Player::Player(int life, int score, int coins, int condition) :
	MovingObject(TextureHolder::instance().getPlayer(I_MARIO), RIGHT, S_MARIO_SIZE, MARIO_LOCATION, 0),
	m_stageFinished(false), m_changedDirection(false), m_reachedTop(false), m_startedJump(false), m_duck(false),
	m_jumpPressed(false), m_hitBrick(false), m_leftBorder(0), m_fieryMario(false), m_keepDucking(false), m_poleDown(false),
	m_life(life), m_hitSideObj(false), m_upKeyReleased(false), m_superMario(false), m_invincible(false), m_jumped(false),
	m_startHeight(0), m_invincibleTime(0), m_points(score), m_coins(coins)
{
	if (condition == I_F_MARIO)
		transformFieryMario();
	else if (condition == I_S_MARIO)
		transformSuperMario();
}

//-----------------------------------------------------------------------------
void Player::move(sf::Time deltaTime)
{
	bool standing, falling;
	if (getPos().y > VIEW_WIDTH && !m_dead)		// The player fell from screen
	{
		kill();
		decLife();
	}

	if (m_poleDown)								// Reached the end of current Stage
	{
		reachedFlagActions(deltaTime);
		return;
	}
	if (m_dead)									// The player have died
	{
		handleDeath(deltaTime);
		return;
	}
	bool fire = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) && m_fieryMario)
		fire = true;
	
	standing = (m_lastPos.x == m_sprite.getPosition().x);
	m_duck = false || m_keepDucking;

	if (m_changedDirection)
		directionChanged(deltaTime);

	moveToSides(deltaTime);
	moveUpDown(deltaTime);
	handleMovement();

	falling = m_reachedTop || (!m_startedJump && m_air) || m_hitBrick;
	playerCheckFalling(falling, deltaTime);

	m_animation.updatePlayer(m_dir,standing,fire,falling || m_jumpPressed,m_duck, m_velocity.x, deltaTime);
	m_animation.setDirection(m_dir);

	varInitialize();
	handleInvincible(deltaTime);
}

//-----------------------------------------------------------------------------
void Player::makeAMove(const float dir_x, sf::Time deltaTime)
{
	// Limiting the speed.
	if (std::abs(m_velocity.x) > (VEL_MAX * deltaTime.asSeconds()))
		m_velocity.x = dir_x * VEL_MAX * deltaTime.asSeconds();

	if (m_velocity.x == 0)		// Giving a boost at the start of movement
	{
		if (m_dir)
			m_velocity.x = START_VEL;
		else
			m_velocity.x = -START_VEL;
	}

	else
		m_velocity.x += dir_x * ACCELERATION * deltaTime.asSeconds();
}

//-----------------------------------------------------------------------------
void Player::decVelocityX(sf::Time deltaTime)
{
	if (std::abs(m_velocity.x) < MIN_DEC)
		m_velocity.x = 0;

	// Making the player slip with drag
	else
	{
		if (m_velocity.x > 0)
			m_velocity.x -= DRAG * deltaTime.asSeconds();
		else
			m_velocity.x += DRAG * deltaTime.asSeconds();
	}

}

//-----------------------------------------------------------------------------
// This function is being used to make the player slip when he change directions.
void Player::directionChanged(sf::Time deltaTime)
{
	if (std::abs(m_velocity.x) > MIN_VELOCITY_X)
	{
		if (m_dir && m_velocity.x < 0)
			m_velocity.x += DRAG * deltaTime.asSeconds();

		else if (!m_dir && m_velocity.x > 0)
			m_velocity.x -= DRAG * deltaTime.asSeconds();
	}
	else
		m_changedDirection = false;
}

//-----------------------------------------------------------------------------
void Player::reachedFlagActions(sf::Time deltaTime)
{
	int endPos = (isFieryOrSuper() ? SUP_MARIO_END_POS : MARIO_END_POS); // Decide ending position

	if (endPos - getPos().y > ERROR_SPACE)					// In case we are above ending position
		m_velocity.y = ENEMY_SPEED * deltaTime.asSeconds();
	
	else if (getPos().y - endPos > ERROR_SPACE)				// In case we are under ending position
		m_velocity.y -= ENEMY_SPEED * deltaTime.asSeconds();
	else
		m_velocity.y = 0;

	m_sprite.move(m_velocity);
	m_animation.pullingFlag(deltaTime);

	m_deathTimePassed += deltaTime.asSeconds();				// Counting the time since he started
	if (m_deathTimePassed > PULING_TIME)					// pulling the flag down
		m_stageFinished = true;
}

//-----------------------------------------------------------------------------
void Player::handleInvincible(sf::Time deltaTime)
{
	if (m_invincible)								// Making the player to flicker if he is invincible
	{
		m_invincibleTime += deltaTime.asSeconds();
		if (m_sprite.getColor() != sf::Color(255, 255, 255, 100))
			m_sprite.setColor(sf::Color(255, 255, 255, 100));
		else
			m_sprite.setColor(sf::Color(255, 255, 255, 255));

		if (m_invincibleTime > INVINCIBLE_TIME)     // If the time for being invincible is passed then stop
		{
			m_sprite.setColor(sf::Color(255, 255, 255, 255));
			m_invincible = false;
			m_invincibleTime = 0;
		}
	}
}

//-----------------------------------------------------------------------------
void Player::moveToSides(sf::Time deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))		 //Left
		goLeft(deltaTime);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))	 //Right
		goRight(deltaTime);
	else
		decVelocityX(deltaTime);									// decrease speed
}

//-----------------------------------------------------------------------------
void Player::moveUpDown(sf::Time deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)            //Jump
		&& !m_reachedTop && m_upKeyReleased && !m_duck)
	{
		jump(deltaTime);

		if (m_jumped)
		{
			AudioHolder::instance().playSound(AUDIO_JUMP);
			m_jumped = false;
		}
	}

	else if (m_jumpPressed) // if we jumped, but stopped pressing the UP key.
		m_reachedTop = true;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)    // Duck
		&& isFieryOrSuper() && !m_air)
		m_duck = true;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		m_upKeyReleased = true;

	if (m_hitBrick)			// If we hit a brick reseting out velocity
	{
		m_velocity.x = 0;
		if (m_air)
			m_velocity.y = BRICK_BUMP * deltaTime.asSeconds();
	}
}

//-----------------------------------------------------------------------------
void Player::varInitialize()
{
	m_startedJump = false;
	m_hitBrick = false;
	m_keepDucking = false;
}

//-----------------------------------------------------------------------------
void Player::handleMovement()
{
	checkGoLeft();						  // Check if player can go left
	m_lastPos = m_sprite.getPosition();   // Save the last position
	m_sprite.move(m_velocity);
	updateLeftBorder();					  // Relocating the screen
	checkStatusJump();					  // Checking if the jump need to be handled
}

//-----------------------------------------------------------------------------
void Player::playerCheckFalling(bool falling, sf::Time deltaTime)
{
	if (falling) // Apply gravity
	{
		fall(deltaTime);
		m_reachedTop = true;
	}
	if (!m_air && !m_startedJump)
		m_velocity.y = 0;
}

//-----------------------------------------------------------------------------
void Player::checkStatusJump()
{
	if (m_reachedTop && !m_air) // Finished the entire jump
	{
		m_reachedTop = false;
		m_jumpPressed = false;
		m_startedJump = false;
		m_upKeyReleased = false;
		m_jumped = true;
		m_velocity.y = 0;
	}
	if (m_hitSideObj)
		m_hitSideObj = false;

	else if (m_hitBrick && !m_reachedTop)
	{
		m_velocity.y = START_VEL;
		m_reachedTop = true;
	}
}

//-----------------------------------------------------------------------------
void Player::jump(sf::Time deltaTime)
{
	if (!m_jumpPressed)
	{
		m_velocity.y = JUMP_START;
		m_startHeight = m_sprite.getPosition().y;
		m_jumpPressed = true;
	}

	if (m_startHeight - m_sprite.getPosition().y > HEIGHT_MAX)
		m_reachedTop = true;

	// Decreasing the velocity of the jump.
	m_velocity.y += JUMP_DEC * deltaTime.asSeconds();
	m_startedJump = true;
}

//-----------------------------------------------------------------------------
void Player::goRight(sf::Time deltaTime)
{
	if (m_dir == LEFT)
		m_changedDirection = true;

	m_dir = RIGHT;
	makeAMove(1, deltaTime);
}

//-----------------------------------------------------------------------------
void Player::goLeft(sf::Time deltaTime)
{
	if (m_dir == RIGHT)
		m_changedDirection = true;

	m_dir = LEFT;
	makeAMove(-1, deltaTime);
}

//-----------------------------------------------------------------------------
void Player::checkGoLeft()
{
	if ((m_sprite.getPosition().x <= 0 ||
		m_leftBorder >= m_sprite.getPosition().x) &&
		m_velocity.x < 0)
		m_velocity.x = 0;
}

//-----------------------------------------------------------------------------
void Player::handleDeath(sf::Time deltaTime)
{
	// Reseting the velocity
	if (m_deathTimePassed == 0)
	{
		AudioHolder::instance().stopBGSound();
		m_velocity = sf::Vector2f(0, 0);
		m_jumpPressed = false;
	}

	// Counting the time
	m_deathTimePassed += deltaTime.asSeconds();

	// At start make him jump, if SWITCH time is passed make him fall
	if (m_deathTimePassed > SWITCH)
		fall(deltaTime);
	else
		jump(deltaTime);

	m_sprite.move(m_velocity);

	// His death is ended
	if (m_deathTimePassed > PLAYER_DEATH_TIME)
		setDelete();
}

//-----------------------------------------------------------------------------
void Player::updateLeftBorder()
{
	// Update left Border position
	if (m_sprite.getPosition().x > VIEW_WIDTH / 2 &&
		m_sprite.getPosition().x > m_leftBorder + VIEW_WIDTH / 2)
		m_leftBorder = m_sprite.getPosition().x - VIEW_WIDTH / 2;
}

//-----------------------------------------------------------------------------
// This function is being used when the player hit an object from the side
void Player::resetVelocity(bool condition)
{
	if (!m_duck || condition)
	{
		m_sprite.setPosition(m_lastPos.x, m_sprite.getPosition().y);
		m_velocity.x = 0;
		m_hitSideObj = true;
	}
	else if (!condition)
		m_keepDucking = true;
}

//-----------------------------------------------------------------------------
void Player::decLife()
{
	m_fieryMario = false;
	m_superMario = false;
	m_life--;
	AudioHolder::instance().playSound(AUDIO_DEATH);
}

//-----------------------------------------------------------------------------
void Player::setPoleDown()
{
	m_poleDown = true;
	m_velocity.x = 0;
}

//-----------------------------------------------------------------------------
void Player::transformSuperMario()
{
	m_superMario = true;
	m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - ICON_SIZE);
	m_animation.changeMarioTexture(TextureHolder::instance().getPlayer(I_S_MARIO), S_MARIO_SIZE);
}

//-----------------------------------------------------------------------------
void Player::transformFieryMario()
{
	m_superMario = false;
	m_fieryMario = true;
	m_sprite.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y - 3);
	m_animation.changeMarioTexture(TextureHolder::instance().getPlayer(I_F_MARIO), F_MARIO_SIZE);
}

//-----------------------------------------------------------------------------
void Player::transformMario()
{
	m_superMario = false;
	m_fieryMario = false;
	m_invincible = true;
	m_animation.changeMarioTexture(TextureHolder::instance().getPlayer(I_MARIO), S_MARIO_SIZE);
}

//-----------------------------------------------------------------------------
void Player::setBrickCond(bool condition)
{
	m_hitBrick = condition;
}

//-----------------------------------------------------------------------------
bool Player::isStageCleared() const
{
	return m_stageFinished;
}

//-----------------------------------------------------------------------------
bool Player::getDirection() const
{
	return m_dir;
}

//-----------------------------------------------------------------------------
float Player::getLeftBorder() const
{
	return m_leftBorder;
}

//-----------------------------------------------------------------------------
bool Player::isFieryOrSuper() const
{
	return m_superMario || m_fieryMario;
}

//-----------------------------------------------------------------------------
bool Player::isInvincible() const
{
	return m_invincible;
}

//-----------------------------------------------------------------------------
bool Player::isFiery() const
{
	return m_fieryMario;
}

//-----------------------------------------------------------------------------
void Player::addPoints(int points)
{
	m_points += points;
}

//-----------------------------------------------------------------------------
int Player::getPoints() const
{
	return m_points;
}

//-----------------------------------------------------------------------------
void Player::addCoin()
{
	m_coins++;
}

//-----------------------------------------------------------------------------
int Player::getCoins() const
{
	return m_coins;
}

//-----------------------------------------------------------------------------
int Player::getLife() const
{
	return m_life;
}

//-----------------------------------------------------------------------------
Player::~Player()
{
}

#pragma once

#include "MovingObject.h"

class Player : public MovingObject
{
public:
	Player(int life,int score, int coins, int condition);

	void addCoin();
	void decLife();
	void setPoleDown();
	int getLife() const;
	int getCoins() const;
	bool isFiery() const;
	int getPoints() const;
	void transformMario();
	bool getDirection() const;
	bool isInvincible() const;
	void addPoints(int points);
	void transformSuperMario();
	void transformFieryMario();
	bool isStageCleared() const;
	float getLeftBorder() const;
	bool isFieryOrSuper() const;
	void setBrickCond(bool condition);
	void resetVelocity(bool condition);
	virtual void move(sf::Time deltaTime);
	void reachedFlagActions(sf::Time deltaTime);
	~Player();
	
private:
	void checkGoLeft();
	void varInitialize();
	void handleMovement();
	void updateLeftBorder();
	void checkStatusJump();
	void jump(sf::Time deltaTime);
	void goLeft(sf::Time deltaTime);
	void goRight(sf::Time deltaTime);
	void moveUpDown(sf::Time deltaTime);
	void moveToSides(sf::Time deltaTime);
	void decVelocityX(sf::Time deltaTime);
	void directionChanged(sf::Time deltaTime);
	void handleInvincible(sf::Time deltaTime);
	virtual void handleDeath(sf::Time deltaTime) override;
	void makeAMove(const float dir_x, sf::Time deltaTime);
	void playerCheckFalling(bool falling, sf::Time deltaTime);

	bool m_changedDirection,
		m_reachedTop,
		m_startedJump,
		m_jumpPressed,
		m_hitBrick,
		m_hitSideObj,
		m_upKeyReleased,
		m_duck,
		m_keepDucking,
		m_superMario,
		m_fieryMario,
		m_invincible,
		m_poleDown,
		m_stageFinished,
		m_jumped;

	float m_startHeight,
		m_leftBorder,
		m_invincibleTime;

	int m_life,
		m_points,
		m_coins;
};
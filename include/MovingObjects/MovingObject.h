#pragma once

#include "GameObject.h"
#include "Animation.h"

class MovingObject : public GameObject
{
public:
	MovingObject(const sf::Texture& data, bool dir, int size,int row, int col);

	void bump();
	void kill();
	void setToAir();
	void squareBump();
	void setGrounded();
	bool isDead() const;
	void setUniqueKill();
	void setPreviousPos();
	void decideDirection();
	void fall(sf::Time deltaTime);
	int getGatheredPoints() const;
	virtual bool isShouldMove() const;
	void setDirection(bool direction);
	void addGatheredPoints(int points);
	sf::Vector2f getDirectionVec() const;
	virtual void move(sf::Time deltaTime);
	void elevate(const MovingObject& platform);
	virtual void squareMove(sf::Time deltaTime);
	void handleDeathTortoise(sf::Time deltaTime);
	~MovingObject();

protected:
	void goDown();
	void goUp();
	void goRight();
	void goLeft();

	virtual void handleDeath(sf::Time deltaTime);
	void sideMove(sf::Time deltaTime, float speed);
	void upDownMove(sf::Time deltaTime, float speed, int top, int bottom, float switchTime);

	Animation m_animation;
	sf::Vector2f m_lastPos,
				 m_velocity;

	bool m_dir,
		m_dead,
		m_air,
		m_shouldMove,
	    m_tortoiseKill;

	float m_deathTimePassed;
	int m_gatheredPoints;

private:

	float m_directionChange;

};
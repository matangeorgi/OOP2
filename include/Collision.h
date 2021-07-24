#pragma once

#include <map>
#include <typeinfo>
#include <typeindex>

#include "AudioHolder.h"
#include "BadMushroom.h"
#include "Block.h"
#include "Brick.h"
#include "Coin.h"
#include "FireBall.h"
#include "FirePole.h"
#include "Floor.h"
#include "FlyingTortoise.h"
#include "GoalFlag.h"
#include "Pipe.h"
#include "PiranaPlants.h"
#include "Platforms.h"
#include "QuestionBlock.h"
#include "SuperMushroom.h"
#include "GoalPole.h"
#include "Tortoise.h"
#include "Player.h"
#include "Fireworks.h"

using HitFunctionPtrMove = void (*)(MovingObject&, MovingObject&);
using HitFunctionPtrStatic = void (*)(MovingObject&, StaticObject&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMapStatic = std::map<Key, HitFunctionPtrStatic>;
using HitMapMove = std::map<Key, HitFunctionPtrMove>;

class Collision
{
public:
	Collision();
	void processMovCollision(MovingObject& object1,
		MovingObject& object2);
	void processStaticCollision(MovingObject& object1,
		StaticObject& object2);

	~Collision();

private:
	HitFunctionPtrMove lookupMove(const std::type_index& class1, const std::type_index& class2);
	HitFunctionPtrStatic lookupStatic(const std::type_index& class1, const std::type_index& class2);
	HitMapMove initializeMovingCollision();
	HitMapStatic initializeStaticCollision();
};
void playerTortoise(MovingObject& player, MovingObject& tortoise);
void playerPlatforms(MovingObject& player, MovingObject& platforms);
void badMushroomTortoise(MovingObject& badMushroom, MovingObject& tortoise);
void playerSupermushroom(MovingObject& player, MovingObject& superMushroom);
void playerBadMushroomOrFly(MovingObject& player, MovingObject& badMushroom);
void playerPiranaPlants(MovingObject& player, MovingObject& piranaPlants);
void playerFireBallPole(MovingObject& player, MovingObject& fireBall);
void EnemyStatic(MovingObject& enemy, StaticObject& staticObj);
void PlayerQuestionBlock(MovingObject& player, MovingObject& questionBlock);
void PlayerCoin(MovingObject& player, MovingObject& coin);
void PlayerFloor(MovingObject& player, StaticObject& floor);
void PlayerStaticCollision(MovingObject& player, StaticObject& staticObj);
int getHeightStatic(MovingObject& player, StaticObject& staticObj);
int getHeightMoving(MovingObject& player, MovingObject& Obj);
bool checkAbove(MovingObject& player, int neededHeight);
bool checkBeneath(MovingObject& player, MovingObject& staticObj);
void checkSides(MovingObject& player, bool condition);
void InitializePoints(sf::Sprite rect, sf::Vector2f& bottomLeft,sf::Vector2f& bottomRight, sf::Vector2f& middlePoint);
void PlayerPipeBlock(MovingObject& player, StaticObject& obj);
void MovingBrick(MovingObject& movable, MovingObject& brick);
void badMushroomBadMushroom(MovingObject& badMushroom1, MovingObject& badMushroom2);
void tortoiseTortoise(MovingObject& tortoise1, MovingObject& tortoise2);
void questionBlockSupMush(MovingObject& questionBlock, MovingObject& superMushroom);
void questionBlockCoin(MovingObject& coin, MovingObject& questionBlock);
void FlagPole(MovingObject& flag, StaticObject& pole);
void PlayerPole(MovingObject& player, StaticObject& pole);
void fireworksEnemy(MovingObject& fireworks, MovingObject& enemy);
void fireworksObj(MovingObject& fireworks, MovingObject& Obj);
void fireworksStaticObj(MovingObject& fireworks, StaticObject& staticObj);

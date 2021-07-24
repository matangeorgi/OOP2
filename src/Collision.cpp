#include "Collision.h"

Collision::Collision()
{
}

//-----------------------------------------------------------------------------
void Collision::processMovCollision(MovingObject& object1,
    MovingObject& object2)
{
    auto phf = lookupMove(typeid(object1), typeid(object2));
    if (!phf) 
        return;

    phf(object1, object2);
}

//-----------------------------------------------------------------------------
HitFunctionPtrMove Collision::lookupMove(const std::type_index& class1, const std::type_index& class2)
{
    static HitMapMove collisionMoveMap = initializeMovingCollision();
    auto mapEntry = collisionMoveMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMoveMap.end())
        return nullptr;

    return mapEntry->second;
}

//-----------------------------------------------------------------------------
void Collision::processStaticCollision(MovingObject& object1,
    StaticObject& object2)
{
    auto phf = lookupStatic(typeid(object1), typeid(object2));
    if (!phf) 
        return;
  
    phf(object1, object2);
}

//-----------------------------------------------------------------------------
HitFunctionPtrStatic Collision::lookupStatic(const std::type_index& class1, const std::type_index& class2)
{
    static HitMapStatic collisionStaticMap = initializeStaticCollision();
    auto mapEntry = collisionStaticMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionStaticMap.end())
        return nullptr;

    return mapEntry->second;
}


//-----------------------------------------------------------------------------
HitMapMove Collision::initializeMovingCollision()
{
    HitMapMove phm;

    // ----------- Enemy Collisions ----------
    phm[Key(typeid(BadMushroom), typeid(Tortoise))] = &badMushroomTortoise;
    phm[Key(typeid(BadMushroom), typeid(BadMushroom))] = &badMushroomBadMushroom;
    phm[Key(typeid(Tortoise), typeid(Tortoise))] = &tortoiseTortoise;
    phm[Key(typeid(BadMushroom), typeid(Brick))] = &MovingBrick;
    phm[Key(typeid(Tortoise), typeid(Brick))] = &MovingBrick;
    phm[Key(typeid(BadMushroom), typeid(QuestionBlock))] = &MovingBrick;
    phm[Key(typeid(Tortoise), typeid(QuestionBlock))] = &MovingBrick;

    // ----------- Object Collisions ----------
    phm[Key(typeid(SuperMushroom), typeid(QuestionBlock))] = &MovingBrick;
    phm[Key(typeid(SuperMushroom), typeid(Brick))] = &MovingBrick;
    phm[Key(typeid(QuestionBlock), typeid(SuperMushroom))] = &questionBlockSupMush;
    phm[Key(typeid(Coin), typeid(QuestionBlock))] = &questionBlockCoin;

    // ----------- Player Collisions ----------
    phm[Key(typeid(Player), typeid(Brick))] = &MovingBrick;
    phm[Key(typeid(Player), typeid(Platforms))] = &playerPlatforms;
    phm[Key(typeid(Player), typeid(Tortoise))] = &playerTortoise;
    phm[Key(typeid(Player), typeid(SuperMushroom))] = &playerSupermushroom;
    phm[Key(typeid(Player), typeid(BadMushroom))] = &playerBadMushroomOrFly;
    phm[Key(typeid(Player), typeid(PiranaPlants))] = &playerPiranaPlants;
    phm[Key(typeid(Player), typeid(FlyingTortoise))] = &playerBadMushroomOrFly;
    phm[Key(typeid(Player), typeid(FireBall))] = &playerFireBallPole;
    phm[Key(typeid(Player), typeid(FirePole))] = &playerFireBallPole;
    phm[Key(typeid(Player), typeid(QuestionBlock))] = &PlayerQuestionBlock;
    phm[Key(typeid(Player), typeid(Coin))] = &PlayerCoin;

    // ----------- Fireworks Collisions ----------
    phm[Key(typeid(Fireworks), typeid(BadMushroom))] = &fireworksEnemy;
    phm[Key(typeid(Fireworks), typeid(PiranaPlants))] = &fireworksEnemy;
    phm[Key(typeid(Fireworks), typeid(FlyingTortoise))] = &fireworksEnemy;
    phm[Key(typeid(Fireworks), typeid(Tortoise))] = &fireworksEnemy;

    phm[Key(typeid(Fireworks), typeid(Brick))] = &fireworksObj;
    phm[Key(typeid(Fireworks), typeid(QuestionBlock))] = &fireworksObj;
    phm[Key(typeid(Fireworks), typeid(Platforms))] = &fireworksObj;

    return phm;
}

//-----------------------------------------------------------------------------
HitMapStatic Collision::initializeStaticCollision()
{
    HitMapStatic phm;
    
    // ----------- Enemy Collisions ---------
    phm[Key(typeid(BadMushroom), typeid(Floor))] = &EnemyStatic;
    phm[Key(typeid(BadMushroom), typeid(Pipe))] = &EnemyStatic;
    phm[Key(typeid(BadMushroom), typeid(Block))] = &EnemyStatic;
    phm[Key(typeid(Tortoise), typeid(Floor))] = &EnemyStatic;
    phm[Key(typeid(Tortoise), typeid(Pipe))] = &EnemyStatic;
    phm[Key(typeid(Tortoise), typeid(Block))] = &EnemyStatic;
    phm[Key(typeid(SuperMushroom), typeid(Block))] = &EnemyStatic;
    phm[Key(typeid(SuperMushroom), typeid(Floor))] = &EnemyStatic;
    phm[Key(typeid(SuperMushroom), typeid(Pipe))] = &EnemyStatic;
   
    // ----------- Object Collisions ----------
    phm[Key(typeid(GoalFlag), typeid(GoalPole))] = &FlagPole;

    // ----------- Player Collisions ----------
    phm[Key(typeid(Player), typeid(Pipe))] = &PlayerPipeBlock;
    phm[Key(typeid(Player), typeid(Floor))] = &PlayerStaticCollision;
    phm[Key(typeid(Player), typeid(Block))] = &PlayerPipeBlock;
    phm[Key(typeid(Player), typeid(GoalPole))] = &PlayerPole;


    // ----------- Fireworks Collisions ----------
    phm[Key(typeid(Fireworks), typeid(Floor))] = &fireworksStaticObj;
    phm[Key(typeid(Fireworks), typeid(Pipe))] = &fireworksStaticObj;
    phm[Key(typeid(Fireworks), typeid(Block))] = &fireworksStaticObj;

    return phm;
}

//-----------------------------------------------------------------------------
void fireworksStaticObj(MovingObject& fireworks, StaticObject& staticObj)
{
    if (checkAbove(fireworks, getHeightStatic(fireworks, staticObj)))
        fireworks.bump();
    else
        fireworks.kill();
}

//-----------------------------------------------------------------------------
void fireworksEnemy(MovingObject& fireworks, MovingObject& enemy)
{
    AudioHolder::instance().playSound(AUDIO_KILL);
    fireworks.kill();
    enemy.setUniqueKill();
}

//-----------------------------------------------------------------------------
void fireworksObj(MovingObject& fireworks, MovingObject& Obj)
{
    if (checkAbove(fireworks, getHeightMoving(fireworks, Obj)))
        fireworks.bump();
    else
        fireworks.kill();
}

//-----------------------------------------------------------------------------
void badMushroomTortoise(MovingObject& badMushroom,
    MovingObject& tortoise)
{
    Tortoise& newTortoise = static_cast<Tortoise&>(tortoise);

    if (newTortoise.getShell() && newTortoise.getJumped())
        badMushroom.setUniqueKill();
    else
    {
        badMushroom.decideDirection();
        tortoise.decideDirection();
    }
}

//-----------------------------------------------------------------------------
void tortoiseTortoise(MovingObject& tortoise1,
    MovingObject& tortoise2)
{
    Tortoise& newTortoise1 = static_cast<Tortoise&>(tortoise1);
    Tortoise& newTortoise2 = static_cast<Tortoise&>(tortoise2);

    if (newTortoise1.getShell() && newTortoise2.getShell()||
        !newTortoise1.getShell() && !newTortoise2.getShell())
    {
        newTortoise1.decideDirection();
        newTortoise2.decideDirection();
    }
    else if (newTortoise1.getShell() && newTortoise1.getJumped() && !newTortoise2.getShell())
        newTortoise2.setUniqueKill();
    else if (!newTortoise1.getShell() && newTortoise2.getJumped() && newTortoise2.getShell())
        newTortoise1.setUniqueKill();
}

//-----------------------------------------------------------------------------
void badMushroomBadMushroom(MovingObject& badMushroom1,
    MovingObject& badMushroom2)
{
    badMushroom1.decideDirection();
    badMushroom2.decideDirection();
}

//-----------------------------------------------------------------------------
void playerPlatforms(MovingObject& player,
    MovingObject& platform)
{
    Player& newPlayer = static_cast<Player&>(player);
    // In case the player is by the side of the platform
    if (checkAbove(player, getHeightMoving(player, platform)))
        newPlayer.elevate(platform);

    // In case the player is under the playform
    else if (player.getPos().y - platform.getPos().y > (ICON_SIZE/2 - 2))
        newPlayer.setBrickCond(true);

    // The player is above the platform
    else
        checkSides(player, true);
}

//-----------------------------------------------------------------------------
void playerTortoise(MovingObject& player,
    MovingObject& tortoise)
{
    if (tortoise.isDead())
        return;

    Player& newPlayer = static_cast<Player&>(player);
    Tortoise& newTortoise = static_cast<Tortoise&>(tortoise);

    if (std::abs(player.getPos().y - getHeightMoving(player, tortoise)) < TORTOISE_GAP)
    {
        if (newTortoise.getShell())      // In case the tortoise is closed
        {
            if (newTortoise.getJumped()) // In case he is closed and moving
                newTortoise.setJumped(false);

            else                         // In case he is closed and static
            {
                newTortoise.setJumped(true);
                newTortoise.setDirection(player.getPos().x);
            }
        }                                // In case he was alive, now we close him
        else
        {
            AudioHolder::instance().playSound(AUDIO_BUMP);
            newPlayer.addPoints(KILL_POINTS);
            newTortoise.setShell();
        }

        newPlayer.bump();
    }    

    // In case we hit the Tortoise by his side.
    else if (!newTortoise.getShell() || (newTortoise.getShell() && newTortoise.getJumped()))
    {
        if (newPlayer.isFieryOrSuper())
            newPlayer.transformMario();

        else if (!newPlayer.isInvincible())
        {
            newPlayer.kill();
            newPlayer.decLife();
        }
    }
}

//-----------------------------------------------------------------------------
void playerSupermushroom(MovingObject& player,
    MovingObject& superMushroom)
{
    SuperMushroom& newSuperMush = static_cast<SuperMushroom&>(superMushroom);

    if (newSuperMush.isShouldMove())
    {
        Player& newPlayer = static_cast<Player&>(player);
        if (!newPlayer.isFieryOrSuper()) // SuperMushroom
            newPlayer.transformSuperMario();

        else if (!newPlayer.isFiery())   // FireFlower
            newPlayer.transformFieryMario();
        superMushroom.setDelete();

        newPlayer.addPoints(SUPER_POINTS);
        AudioHolder::instance().playSound(AUDIO_SUPER);
    }
}

//-----------------------------------------------------------------------------
void playerBadMushroomOrFly(MovingObject& player,
    MovingObject& badMushroom)
{
    if (badMushroom.isDead())
        return;

    Player& newPlayer = static_cast<Player&>(player);
    if (badMushroom.isDead() || newPlayer.isInvincible())
        return;

    // In case we jumped over the mushroom.
    if (std::abs(player.getPos().y - getHeightMoving(player, badMushroom)) < MUSHROOM_GAP)
    {
        badMushroom.kill();
        newPlayer.bump();
        newPlayer.addPoints(KILL_POINTS);
        AudioHolder::instance().playSound(AUDIO_BUMP);
    }

    // In case the mushroom hit us.
    else if (newPlayer.isFieryOrSuper())
        newPlayer.transformMario();
        
    else
    {
        newPlayer.kill();
        newPlayer.decLife();
    }
}

//-----------------------------------------------------------------------------
void playerPiranaPlants(MovingObject& player,
    MovingObject& PiranaPlants)
{
    Player& newPlayer = static_cast<Player&>(player);

     if (newPlayer.isFieryOrSuper())
        newPlayer.transformMario();

     else if (!newPlayer.isInvincible())
     {
         newPlayer.kill();
         newPlayer.decLife();
     }
}

//-----------------------------------------------------------------------------
void playerFireBallPole(MovingObject& player,
    MovingObject& FireBall)
{
    Player& newPlayer = static_cast<Player&>(player);
    sf::Vector2f bottomLeft, bottomRight, middlePoint;

    // Calling the function to calculate where the obstacle is.
    InitializePoints(FireBall.draw(), bottomLeft, bottomRight, middlePoint);

    if (player.draw().getGlobalBounds().contains(bottomLeft)||
        player.draw().getGlobalBounds().contains(bottomRight)||
        player.draw().getGlobalBounds().contains(middlePoint))
    {
        if (newPlayer.isFieryOrSuper())
            newPlayer.transformMario();
        else if (!newPlayer.isInvincible())
        {
            newPlayer.kill();
            newPlayer.decLife();
        }
    }
}

//-----------------------------------------------------------------------------
// The questionBlock will hold mario's state to know what to pull out.
void PlayerQuestionBlock(MovingObject& player,
    MovingObject& questionBlock)
{
    QuestionBlock& newquestionBlock = static_cast<QuestionBlock&>(questionBlock);
    if (checkBeneath(player, questionBlock) && !newquestionBlock.isOpen())
    {
        if (questionBlock.draw().getGlobalBounds().contains(player.getPos().x + ICON_SIZE / 2, player.getPos().y))
        {
            Player& newPlayer = static_cast<Player&>(player);
            newquestionBlock.squareBump();
            newquestionBlock.setOpen(newPlayer.isFieryOrSuper());
            AudioHolder::instance().playSound(AUDIO_BUMP);
        }
    }
    else if(!checkAbove(player,getHeightMoving(player,questionBlock)))
        checkSides(player,true);
}

//-----------------------------------------------------------------------------
void PlayerCoin(MovingObject& player,
    MovingObject& coin)
{
    Coin& newCoin = static_cast<Coin&>(coin);
    if (!newCoin.getTaken())
    {
        Player& newPlayer = static_cast<Player&>(player);
        newCoin.setTaken();
        newPlayer.addCoin();
        newPlayer.addPoints(COIN_POINTS);
        AudioHolder::instance().playSound(AUDIO_COIN);
    }
}

//-----------------------------------------------------------------------------
// Telling the supermushroom which object to pull out.
void questionBlockSupMush(MovingObject& questionBlock, MovingObject& superMushroom)
{
    QuestionBlock& newquestionBlock = static_cast<QuestionBlock&>(questionBlock);
    SuperMushroom& newSuperMush = static_cast<SuperMushroom&>(superMushroom);
    if (newquestionBlock.isOpen() && !newSuperMush.isShouldMove() &&
        questionBlock.draw().getGlobalBounds().contains(newSuperMush.getPos().x + ICON_SIZE / 2, newSuperMush.getPos().y))
    {
        newSuperMush.setKind(newquestionBlock.getKind());
        newSuperMush.setShouldMove();
    }
}

//-----------------------------------------------------------------------------
void questionBlockCoin(MovingObject& coin, MovingObject& questionBlock)
{
    QuestionBlock& newquestionBlock = static_cast<QuestionBlock&>(questionBlock);
    Coin& newCoin = static_cast<Coin&>(coin);
    if (newquestionBlock.isOpen() && !newCoin.getTaken())
    {
        newCoin.setTaken();
        newCoin.addGatheredPoints(COIN_POINTS);
        AudioHolder::instance().playSound(AUDIO_COIN);
    }
}

//------------------------- Moving and Static Functions -----------------------

//-----------------------------------------------------------------------------
void FlagPole(MovingObject& flag, StaticObject& pole)
{
    GoalPole& newPole = static_cast<GoalPole&>(pole);
    if (newPole.isPlayerReached())  // If the player reached the pole, the flag will go down.
    {
        GoalFlag& newFlag = static_cast<GoalFlag&>(flag);
        newFlag.setShouldMove();
    }
}

//-----------------------------------------------------------------------------
void PlayerPole(MovingObject& player, StaticObject& pole)
{
    if (player.draw().getGlobalBounds().contains(pole.getPos().x + ICON_SIZE*2, player.getPos().y))
    {
        Player& newPlayer = static_cast<Player&>(player);
        GoalPole& newPole = static_cast<GoalPole&>(pole);
        newPlayer.setPoleDown();
        newPole.setPlayerReached();
    }
}

//-----------------------------------------------------------------------------
void EnemyStatic(MovingObject& enemy,
                    StaticObject& staticObj)
{
    if (!enemy.isShouldMove())
        return;

    if (!checkAbove(enemy, getHeightStatic(enemy, staticObj)))
            enemy.decideDirection();
}

//-----------------------------------------------------------------------------
void PlayerPipeBlock(MovingObject& player, 
    StaticObject& obj)
{
    bool condition;

    // We are above the Pipe
    condition = checkAbove(player, getHeightStatic(player, obj));

    // We are by the side of the Pipe
    if (!condition)
        checkSides(player, true);
}

//-----------------------------------------------------------------------------
void PlayerFloor(MovingObject& player,
    StaticObject& floor)
{
    player.setGrounded();
}

//-----------------------------------------------------------------------------
void MovingBrick(MovingObject& movable, MovingObject& brick)
{
    if (movable.isDead())
        return;

    // In case there is an enemy above the brick we can kill it.
    if (brick.getDirectionVec().y < 0 && movable.getPos().y < brick.getPos().y)
    {
        movable.setUniqueKill();
        if (movable.getDirectionVec().x > 0)
            movable.setDirection(LEFT);
        else
            movable.setDirection(RIGHT);
        movable.elevate(brick);
    }

    bool condition = checkBeneath(movable, brick);
    int neededheight = getHeightMoving(movable, brick);

    if (condition && 
        brick.draw().getGlobalBounds().contains(movable.getPos().x + ICON_SIZE / 2, movable.getPos().y))
        brick.squareBump();

    if (!condition)
        condition = checkAbove(movable, neededheight);

    if (!condition)
        checkSides(movable, false);
}
//-----------------------------------------------------------------------------
void PlayerStaticCollision(MovingObject& player,
    StaticObject& staticObj)
{
    int neededheight = getHeightStatic(player, staticObj);
    if(!checkAbove(player, neededheight))
        checkSides(player, false);
}

//-----------------------------------------------------------------------------
int getHeightStatic(MovingObject& player, StaticObject& staticObj)
{
    return staticObj.getPos().y - player.draw().getScale().y * player.draw().getTexture()->getSize().y;
}

//-----------------------------------------------------------------------------
int getHeightMoving(MovingObject& player, MovingObject& Obj)
{
    return Obj.getPos().y - player.draw().getScale().y * player.draw().getTexture()->getSize().y;
}

//-----------------------------------------------------------------------------
bool checkAbove(MovingObject& player, int neededHeight)
{
    if (std::abs(player.getPos().y - neededHeight) < STATIC_GAP)
    {
        player.setGrounded();
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------
bool checkBeneath(MovingObject& player, MovingObject& staticObj)
{
     if (player.getPos().y - staticObj.getPos().y > (ICON_SIZE - GAP_BENEATH))
     {
        Player& newPlayer = static_cast<Player&>(player);
        newPlayer.setBrickCond(true);
        return true;
     }
     return false;
}

//-----------------------------------------------------------------------------
void checkSides(MovingObject& player, bool condition)
{
    Player& newPlayer = static_cast<Player&>(player);
    newPlayer.resetVelocity(condition);
}

//-----------------------------------------------------------------------------
void InitializePoints(sf::Sprite rect,sf::Vector2f& bottomLeft, 
                      sf::Vector2f& bottomRight, sf::Vector2f& middlePoint)
{
    sf::Vector2f topLeft = rect.getTransform().transformPoint(sf::Vector2f(0, 0));
    sf::Vector2f topRight = rect.getTransform().transformPoint(sf::Vector2f(rect.getTexture()->getSize().x, 0));
    bottomLeft = rect.getTransform().transformPoint(sf::Vector2f(0, rect.getTexture()->getSize().y));
    bottomRight = rect.getTransform().transformPoint(sf::Vector2f(rect.getTexture()->getSize().x, rect.getTexture()->getSize().y));
    middlePoint.x = (topRight.x + bottomRight.x) / 2;
    middlePoint.y = (topRight.y + bottomRight.y) / 2;
}

//-----------------------------------------------------------------------------
Collision::~Collision()
{
}



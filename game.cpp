/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

/***************************************
* GAME :: DESTRUCTOR
* free the memory
***************************************/
Game::~Game()
{
	//delete rocks
	for (int i = 0;i < rocks.size();++i)
		delete rocks[i];
	//delete bullets
	for (int i = 0;i < bullets.size();++i)
		delete bullets[i];	
}



/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
***************************************/
void Game::advance()
{
	advanceRocks();
	advanceBullets();
	advanceShip();

	handleCollisions();
	cleanUpZombies();
}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{
	//handle the directions of the ship
	if (ui.isLeft())
	{
		ship.rotateLeft();
	}
	if (ui.isRight())
	{
		ship.rotateRight();
	}

	//move ship in the direction it is pointing 
	if (ui.isUp())
	{
		ship.move();
	}

	// shoot bullets
	if (ui.isSpace() && ship.isAlive())
	{
		bullets.push_back(new Bullet());
		bullets.back()->fire(ship.getPoint(), ship.getVelocity(), ship.getAngle());
	}
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{
	drawRocks();
	drawBullets();
	drawShip();
	
}

/*********************************************
* GAME :: DRAWBULLETS
* Draw the bullets, if they are alive
*********************************************/
void Game::drawBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
		{
			bullets[i]->draw();
		}
	}
}

/*********************************************
* GAME :: DRAWBULLETS
* Draw the rocks, if they are alive
*********************************************/
void Game::drawRocks()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			rocks[i]->draw();
		}
	}
}

/*********************************************
* GAME :: DRAWSHIP
* Draw the ship, if it is alive
*********************************************/
void Game::drawShip()
{
	if (ship.isAlive())
	{
		ship.draw();
	}
}


/***************************************
* GAME :: ADVANCE ROCKS
* Go through each rock and advance it.
* If they leave the screen bring them back
***************************************/
void Game::advanceRocks()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			// this rocks is alive, tell it to move forward
			rocks[i]->advance();
 
			keepOnScreen(rocks[i]);
		}
	}
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
* If they leave the screen bring them back
***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->isAlive())
		{
			// this bullet is alive, tell it to move forward
			bullets[i]->advance();

			keepOnScreen(bullets[i]); //pass the pointer
		}
	}
}

/***************************************
* GAME :: ADVANCE Ship
* If it leaves the screen bring it back
***************************************/
void Game::advanceShip()
{
	if (ship.isAlive())
	{
		ship.advance();
		keepOnScreen(&ship); //pass the address
	}
}

/**************************************************************************
* GAME :: IN HORIZONTAL BORDERS
* Determines if a given point is inside the horizontal borders of the screen
**************************************************************************/
bool Game::inHorizontalBorders(const Point & point)
{
	return ( point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
* GAME :: IN VERTICAL BORDERS
* Determines if a given point is inside the vertical borders of the screen
**************************************************************************/
bool Game::inVerticalBorders(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
* GAME :: KEEP ON SCREEN
* Checks if the flying object left the screen. If it did it brings it back.
* To avoid copy-paste for each flying object we use polymorphism
**************************************************************************/
void Game::keepOnScreen(FlyingObject* flyingObject)
{
	//if it left the vertical borders
	if (!inVerticalBorders(flyingObject->getPoint()))
	{
		flyingObject->bringBackVertically();
	}//if it left the horizontal borders
	else if (!inHorizontalBorders(flyingObject->getPoint()))
	{
		flyingObject->bringBackHorizontally();
	}
}

/**************************************************************************
* GAME :: CREATE ROCKS
* Create BIG_ROCKS_NUM rocks witha random postion on the screen 
**************************************************************************/
void Game::createRocks()
{
	for (int i = 0;i < BIG_ROCKS_NUM;++i)
	{
		float randomY = random(bottomRight.getY(), topLeft.getY());
		rocks.push_back(new BigRock(Point(topLeft.getY(), randomY)));
	}
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
* Check for a collision between a bird and a bullet.
**************************************************************************/
void Game::handleCollisions()
{

}

/**************************************************************************
* GAME :: HANDLE COLLISIONS BULLETS ROCKS
* Check for a collision between bullets and rocks.
**************************************************************************/
void Game::handleCollisionsBulletsRocks()
{

}

/**************************************************************************
* GAME :: HANDLE COLLISIONS SHIP ROCKS
* Check for a collision between the ship and rocks.
**************************************************************************/
void Game::handleCollisionsShipRocks()
{

}

/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets and rock out of the list)
**************************************************************************/
void Game::cleanUpZombies()
{
	
	

}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}


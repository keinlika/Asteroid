#ifndef rocks_h
#define rocks_h
#include <cmath>
#define PI 3.14

//radius
#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

// Define the following classes here:
//   Rock
//   BigRock
//   MediumRock
//   SmallRock

#include "orientedObject.h"
#include "uiDraw.h"
#include "vector"
/*********************************************
* SHIP
* Everything ship needs to survive in the space
*********************************************/
class Rock : public OrientedObject
{
public:
	/****************
	* CONSTRUCTORS
	*****************/
	Rock() : OrientedObject() { } //call the default constructor of orientedObject
	Rock(const Point&point) : OrientedObject(point) { }
	Rock(const Point&point, const Velocity&velocity, float angle) 
		: OrientedObject(point, velocity, angle) { }

	virtual void draw() = 0;
	virtual int  getSize() = 0;
	virtual void kill(std::vector<Rock*> &rocks) = 0;
	//keeping the base class advance definition
};

// TODO - ask how to make in UML pure virtual
// TODO - ask B Comeau about the window size can i keep it in a header
// beacuse I can't assume here to be -200 200 that is tight coupling 
//and if the size changes it fails later, I'm leaving the 0,.0 for now
class BigRock : public Rock
{
public:
	/****************
	* CONSTRUCTORS
	*****************/
	BigRock() : Rock() { initialize(); }
	BigRock(const Point&point) : Rock(point) { initialize(); }
	BigRock(const Point&point, const Velocity&velocity, float angle)
		: Rock(point, velocity, angle) { }

	virtual void draw();
	virtual int  getSize() { return BIG_ROCK_SIZE; }
	virtual void advance(); //overriding 
	virtual void kill(std::vector<Rock*> &rocks);
private:
	void initialize();
};

class MediumRock : public Rock
{
public:
	/****************
	* CONSTRUCTORS
	*****************/
	MediumRock()
	{

	}
	MediumRock(const Point&point) : Rock(point) { }
	MediumRock(const Point&point, const Velocity&velocity, float angle)
		: Rock(point, velocity, angle) { }

	virtual void draw();
	virtual int  getSize() { return MEDIUM_ROCK_SPIN; }
	virtual void advance(); //overriding 
	virtual void kill(std::vector<Rock*> &rocks); //overriding 
};

class SmallRock : public Rock
{
public:
	/****************
	* CONSTRUCTORS
	*****************/
	SmallRock()
	{

	}
	SmallRock(const Point&point) : Rock(point) { }
	SmallRock(const Point&point, const Velocity&velocity, float angle)
		: Rock(point, velocity, angle) { }

	virtual void draw();
	virtual int  getSize() { return SMALL_ROCK_SIZE; }
	virtual void advance(); //overriding 
	virtual void kill(std::vector<Rock*> &rocks); //overriding
};




#endif /* rocks_h */

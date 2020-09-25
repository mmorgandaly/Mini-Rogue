#include "Dungeon.h"
#include "utilities.h"
#include "Monsters.h"

#include <iostream>
using namespace std;

Monsters::Monsters(Dungeon* d, int r, int c)
	:m_dungeon(d), m_row(r), m_col(c)
{

}

bool Monsters::isDead() const			//dead if hitpoints = 0
{
	return m_hitpoints == 0;
}

 int Monsters::col() const
 {
	 return m_col;
 }

int Monsters::row() const
{
	return m_row;
}

/////////////////////////SNAKEWOMEN/////////////////////////////////

Snakewomen::Snakewomen(Dungeon* ap, int r, int c) 
	:Monsters(ap,r,c), m_health(0),
	m_hitpoints(randInt(3,6)), m_armor(3), m_dexterity(3), m_strength(2)
{
	if (ap == nullptr)
	{
		cout << "***** A Snakewomen must be created in some Arena!" << endl;		//error if coordinates are wrong
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		cout << "***** Snakewoman created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}

}


bool Snakewomen::isDead() const			//dead if hitpoints = 0
{
	return m_hitpoints == 0;
}

int Snakewomen::hitpoints() const     //get hitpoints
{
	return m_hitpoints;
}

int Snakewomen::armor() const     //get armor
{
	return m_armor;
}

int Snakewomen::dexterity() const     //get dexterity
{
	return m_dexterity;
}

int Snakewomen::strength() const		//get strength
{
	return m_strength;
}

void Monsters::move()
{
	int ddir = randInt(0, 3);  // dir is now UP, DOWN, LEFT, or RIGHT
	char dir;
	switch (ddir)
	{
	case 0: dir = ARROW_UP; break;
	case 1: dir = ARROW_DOWN; break;
	case 2: dir = ARROW_LEFT; break;
	case 3: dir = ARROW_RIGHT; break;
	}
	m_dungeon->determineNewPosition(m_row, m_col, dir); //new position
}

void Monsters::follow(int dir) //determine new position in direction
{
	m_dungeon->determineNewPosition(m_row, m_col, dir);
}
void Snakewomen::getAttacked()	//hitpoints decreases if attacked
{
	if(m_dungeon->dexterityProbability() == "hits.")
	m_hitpoints--;
}

///////////////////////BOGEYMEN////////////////////////////


Bogeymen::Bogeymen(Dungeon* ap, int r, int c)
	: Monsters(ap,r,c),m_hitpoints(randInt(5,10)), m_armor(2), m_dexterity(randInt(2,3)), m_strength(randInt(2,3))
{
	if (ap == nullptr)
	{
		cout << "***** A Bogeyman must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		cout << "***** Bogeyman created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}

}


bool Bogeymen::isDead() const
{
	return m_hitpoints == 0;
}

int Bogeymen::hitpoints() const
{
	return m_hitpoints;
}

int Bogeymen::armor() const
{
	return m_armor;
}

int Bogeymen::dexterity() const
{
	return m_dexterity;
}

int Bogeymen::strength() const
{
	return m_strength;
}

void Bogeymen::getAttacked()
{
	if (m_dungeon->dexterityProbability() == "hits")
	m_hitpoints--;
}

void Bogeymen::follow(int dir)
{
	m_dungeon->determineNewPosition(m_row, m_col, dir);
}

//////////////////////DRAGONS/////////////////////////////

Dragons::Dragons(Dungeon* ap, int r, int c)
	: Monsters(ap,r,c), m_health(0),
	m_hitpoints(randInt(20,25)), m_armor(4), m_dexterity(4), m_strength(4), m_maxhp(m_hitpoints) //idk if that allowed but
{
	if (ap == nullptr)
	{
		cout << "***** A Dragon must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		cout << "***** Dragon created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}

}


bool Dragons::isDead() const
{
	return m_hitpoints == 0;
}

int Dragons::hitpoints() const
{
	return m_hitpoints;
}

int Dragons::armor() const
{
	return m_armor;
}

int Dragons::dexterity() const
{
	return m_dexterity;
}

int Dragons::strength() const
{
	return m_strength;
}

int Dragons::maxhp() const
{
	return m_maxhp;
}

void Dragons::getAttacked()
{
	if (m_dungeon->dexterityProbability() == "hits.")
	m_hitpoints--;
}
////////////////GOBLINS//////////////////

Goblins::Goblins(Dungeon* ap, int r, int c)
	: Monsters(ap,r,c), m_health(0),
	m_hitpoints(randInt(15,20)), m_armor(1), m_dexterity(1), m_strength(3)
{
	if (ap == nullptr)
	{
		cout << "***** A Goblin must be created in some Arena!" << endl;
		exit(1);
	}
	if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
	{
		cout << "***** Goblin created with invalid coordinates (" << r << ","
			<< c << ")!" << endl;
		exit(1);
	}

}



bool Goblins::isDead() const
{
	return m_hitpoints <= -1;       //not sure why, but only works with -1
}

int Goblins::hitpoints() const
{
	return m_hitpoints;
}

int Goblins::armor() const
{
	return m_armor;
}

int Goblins::dexterity() const
{
	return m_dexterity;
}

int Goblins::strength() const
{
	return m_strength;
}

void Goblins::getAttacked()
{
	if (m_dungeon->dexterityProbability() == "hits.")
	{
		m_hitpoints--;
	}
}
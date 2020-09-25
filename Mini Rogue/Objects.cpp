#include "Objects.h"
#include "Dungeon.h"
#include "utilities.h"
#include "Player.h"
#include "Monsters.h"

#include<iostream>
using namespace std;

Weapons::Weapons(int dmg, int dxt)
	: m_damage(dmg), m_dexterity(dxt), m_player(nullptr), m_dungeon(nullptr)
{}

int Weapons::row() const
{
	return m_row;
}

int Weapons::col() const
{
	return m_col;
}

int Weapons::damage() const
{
	return m_damage;
}

int Weapons::dexterity() const
{
	return m_dexterity;
}

int Weapons::damagePoints()
{
	int dp = 0;
	if (m_dungeon->attack() == "goblins")
		 dp = randInt(0, m_goblins[0]->strength() + damage() - 1); //attacker strength
	if (m_dungeon->attack() == "dragons")
		dp = randInt(0, m_dragons[0]->strength() + damage() - 1); //attacker strength
	if (m_dungeon->attack() == "bogeymen")
		dp = randInt(0, m_bogeymen[0]->strength() + damage() - 1); //attacker strength
	if (m_dungeon->attack() == "snakewomen")
		dp = randInt(0, m_snakewomen[0]->strength() + damage() - 1); //attacker strength
	return dp;
}

bool Weapons::dexterityBonus()
{
	//goblin attacks player 
	//int attackerpoints = m_goblins[0]->dexterity() + dexterity();
	//int defenderpoints = m_player->dexterity() + dexterity();
	//if (randInt(1, 5) >= randInt(1, defenderpoints))
		return true;		//attacker has hit the defender
}
Maces::Maces()
	: Weapons(2, 0)

{

}

ShortSwords::ShortSwords()
	: Weapons(2, 0)

{

}

LongSwords::LongSwords()
	: Weapons(4, 2)

{

}

MagicAxes::MagicAxes()
	: Weapons(5, 5)

{

}


MagicFangs::MagicFangs()
	: Weapons(2, 3)

{

}

Stairs::Stairs(Dungeon* d, int r, int c)
	:m_dungeon(d), m_row(r), m_col(c)
{}

int Stairs::row() const
{
	return m_row;
}

int Stairs::col() const
{
	return m_col;
}

void Stairs::randomCoords(int r, int c)
{

	r = randInt(2, 17);
	c = randInt(2, 69);
	m_row = r;
	m_col = c;
}

Scrolls::Scrolls(Dungeon* d, int r, int c)
	:m_row(r), m_col(c), m_dungeon(d)
{

}

Teleportation::Teleportation(Dungeon* d, int r, int c)
	: Scrolls(d, r, c)
{

}

Strength::Strength(Dungeon* d, int r, int c)
	: Scrolls(d, r, c)
{

}

Armor::Armor(Dungeon* d, int r, int c)
	: Scrolls(d, r, c)
{

}

Health::Health(Dungeon* d, int r, int c)
	: Scrolls(d, r, c)
{

}

Dexterity::Dexterity(Dungeon* d, int r, int c)
	: Scrolls(d, r, c)
{

}

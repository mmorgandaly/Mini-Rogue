#ifndef OBJECTS_H
#define OBJECTS_H

class Dungeon;
class Player;
class Snakewomen;
class Bogeymen;
class Dragons;
class Goblins;

class Weapons
{
public:
	Weapons(int dmg, int dxt);
	int row() const;
	int col() const;
	int damage() const;
	int dexterity() const;
	int damagePoints();
	bool dexterityBonus();

private:
	int m_row;
	int m_col;
	int m_damage;
	int m_dexterity;
	Dungeon* m_dungeon;
	Player* m_player;
	Snakewomen* m_snakewomen[6];       
	Bogeymen* m_bogeymen[7];        
	Dragons* m_dragons[7];        
	Goblins* m_goblins[6];        
};

class Maces :public Weapons
{ 
public:
	Maces();

private:

};

class ShortSwords :public Weapons
{
public:
	ShortSwords();

private:

};

class LongSwords :public Weapons
{
public:
	LongSwords();

private:

};

class MagicAxes :public Weapons
{
public:
	MagicAxes();

private:

};

class MagicFangs :public Weapons
{
public:
	MagicFangs();
private:
	Player* m_player;
};

class Stairs
{
public:
	Stairs(Dungeon* d, int r, int c);

	int row() const;
	int col() const;
	void randomCoords(int r, int c);

private:
	Dungeon* m_dungeon;
	int m_row;
	int m_col;
};

class Scrolls
{
public:
	Scrolls(Dungeon* d, int r, int c);

	int row() const;
	int col() const;

private:
	Dungeon* m_dungeon;
	int m_row;
	int m_col;
};

class Teleportation :public Scrolls
{
public:
	Teleportation(Dungeon* d, int r, int c);
};

class Armor : public Scrolls
{
public:
	Armor(Dungeon* d, int r, int c);
};

class Strength : public Scrolls
{
	Strength(Dungeon* d, int r, int c);
};

class Health : public Scrolls
{
	Health(Dungeon* d, int r, int c);
};

class Dexterity : public Scrolls
{
	Dexterity(Dungeon* d, int r, int c);
};
#endif //OBJECTS_H
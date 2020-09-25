#ifndef MONSTERS_H
#define MONSTERS_H

class Dungeon;


class Monsters
{
public:
	Monsters(Dungeon* d, int r, int c);
	int row() const;
	int col() const;
	void follow(int dir);
	void move();
	bool isDead() const;
	//int hitpoints() const;
	//int armor() const;
	//int dexterity() const;
	//int strength() const;

private:
	Dungeon* m_dungeon;
	int m_row;
	int m_col;
	int m_hitpoints;

};

class Snakewomen : public Monsters
{
public:
	Snakewomen(Dungeon* ap, int r, int c);

	int  row() const;
	int  col() const;
	 bool isDead() const;
	int hitpoints() const;
	int armor() const;
	int dexterity() const;
	int strength() const;

	void getAttacked();
	//void follow(int dir);
	//void move();


private:
	Dungeon* m_dungeon;
	int    m_row;
	int    m_col;
	int    m_health;
	int m_hitpoints;
	int m_armor;
	int m_dexterity;
	int m_strength;
};

class Bogeymen :public Monsters
{
public:
	Bogeymen(Dungeon* ap, int r, int c);

	int  row() const;
	int  col() const;
	bool isDead() const;
	int hitpoints() const;
	int armor() const;
	int dexterity() const;
	int strength() const;

	void getAttacked();
	void follow(int dir);

private:
	Dungeon* m_dungeon;
	int    m_row;
	int    m_col;
	int    m_health;
	int m_hitpoints;
	int m_armor;
	int m_dexterity;
	int m_strength;
};

class Dragons: public Monsters
{
public:
	Dragons(Dungeon* ap, int r, int c);

	int  row() const;
	int  col() const;
	bool isDead() const;
	int hitpoints() const;
	int armor() const;
	int dexterity() const;
	int strength() const;
	void getAttacked();
	int maxhp() const;

private:
	Dungeon* m_dungeon;
	int    m_row;
	int    m_col;
	int    m_health;
	int m_hitpoints;
	int m_armor;
	int m_dexterity;
	int m_strength;
	int m_maxhp;
};

class Goblins : public Monsters
{
public:
	Goblins(Dungeon* ap, int r, int c);

	int  row() const;
	int  col() const;
	bool isDead() const;
	int hitpoints() const;
	int armor() const;
	int dexterity() const;
	int strength() const;

	void getAttacked();

private:
	Dungeon* m_dungeon;
	int    m_row;
	int    m_col;
	int    m_health;
	int m_hitpoints;
	int m_armor;
	int m_dexterity;
	int m_strength;
};

#endif //MONSTERS_H
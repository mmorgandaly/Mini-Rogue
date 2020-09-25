#ifndef PLAYER_H
#define PLAYER_H

using namespace std;
class Dungeon;
class Maces;


class Player 
{
public:
    Player(Dungeon* ap, int r, int c);
    void move(char dir);
    bool isDead() const;
    void setDead();
    void getAttacked();
    void cheat();
    void showInventory();
    void randomCoords(int r, int c);
    void increaseHP();


    int row() const;
    int col() const;
    int hitpoints() const;
    int armor() const;
    int dexterity() const;
    int strength() const;
    int maxhp() const;

private:
    Dungeon* m_dungeon;
    int    m_row;
    int    m_col;
    int m_hitpoints;
    int m_armor;
    int m_dexterity;
    int m_strength;
    int m_maxhp;
    Maces* m_maces;

};
#endif //PLAYER_H
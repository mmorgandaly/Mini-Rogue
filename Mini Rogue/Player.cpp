#include "Player.h"
#include "Dungeon.h"
#include "utilities.h"
#include "Objects.h"

#include <iostream>
using namespace std;

Player::Player(Dungeon* ap, int r, int c)
    :m_dungeon(ap), m_row(r), m_col(c),       //initialize actors so member variables are automatically added
    m_hitpoints(20), m_armor(2), m_dexterity(2), m_strength(2), m_maxhp(20)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Dungeon!" << endl;        //print error message if dungeon is wrong size
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
}

void Player::move(char dir)
{
    int r = m_row;
    int c = m_col;

    if (m_dungeon->determineNewPosition(r, c, dir)) //not true if hits a wall or monster
    {
            m_row = r;          //change row and cols accordingly
            m_col = c;
   }  
}

int Player::row() const     //get row
{
    return m_row;
}

int Player::col() const     //get col
{
    return m_col;
}

int Player::hitpoints() const     //get hitpoints
{
    return m_hitpoints;
}

int Player::armor() const     //get armor
{
    return m_armor;
}

int Player::dexterity() const     //get dexterity
{
    return m_dexterity;
}

int Player::strength() const     //get strength
{
    return m_strength;
}

bool Player::isDead() const
{
    return m_hitpoints ==-1;       //not sure why, but only works with -1
}

void Player::setDead()          //dead if hitpoints = 0
{
    m_hitpoints = 0;
}

int Player::maxhp() const       //return max amount of hitpoints
{
    return m_maxhp;
}

void Player::getAttacked()
{ 
    //if (m_maces->dexterityBonus()) //= m_maces->damagePoints();
 // if(m_dungeon->dexterityProbability() == "hits.")
       m_hitpoints--;   
}

void Player::cheat()        // press c to cheat
{
    m_hitpoints = 50;
    m_strength = 9;
    m_maxhp = 50;
}

void Player::showInventory()    //show inventory of items
{
    clearScreen();
    cout << "Inventory:" << endl;
}

void Player::randomCoords(int r, int c)
{
      r = randInt(2, 17);
      c = randInt(2, 69);
      m_row = r;
      m_col = c;
}

void Player::increaseHP()
    {
        m_hitpoints++;
    }

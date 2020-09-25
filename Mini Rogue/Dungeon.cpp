#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"
#include "Monsters.h"
#include "Objects.h"

#include<iostream>
using namespace std;

Dungeon::Dungeon(int nRows, int nCols)              //constructor
    : m_rows(nRows), m_cols(nCols), m_turns(0), m_level(0), m_player(nullptr), m_stairs(nullptr),
    totalsnakewomen(0), totalbogeymen(0), totaldragons(0), totalgoblins(0)
{
    if (nRows <= 0 || nCols <= 0 || nRows > 18 || nCols > 70)
    {
        cout << "***** Dungeon created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);                                                    //exit if not right dungeon size
    }
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, 0);         //sets everything to 0
}

Dungeon::~Dungeon() //destructor deletes all allocated objects
{
    for (int j = 0; j < totalsnakewomen; j++)       //delete snakewomen
        delete m_snakewomen[j];
    for (int k = 0; k < totalbogeymen; k++)         //delete bogeymen
        delete m_bogeymen[k];
    for (int k = 0; k < totaldragons; k++)          //delete dragons
        delete m_dragons[k];
    for (int k = 0; k < totalgoblins; k++)          //delete goblins
        delete m_goblins[k];
    delete m_player;                                //delete player
    delete m_stairs;                                 //delete stair

}

int Dungeon::rows() const       //get rows
{
    return m_rows;
}

int Dungeon::cols() const       //get cols
{
    return m_cols;
}

int Dungeon::level() const         //get level
{
    return m_level;
}

int Dungeon::getCellStatus(int r, int c) const  //returns what is at grid
{
    checkPos(r, c, "Dungeon::getCellStatus");
    return m_grid[r - 1][c - 1];
}

void Dungeon::setCellStatus(int r, int c, int status)   //sets what is at grid
{
    checkPos(r, c, "Dungeon::setCellStatus");
    m_grid[r - 1][c - 1] = status;
}

bool Dungeon::isPosInBounds(int r, int c) const     //checks if in bounds
{
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}

void Dungeon::checkPos(int r, int c, string functionName) const //if not in bounds, exits
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid dungeon position (" << r << ","
            << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

Player* Dungeon::player() const     //returns player
{
    return m_player;
}

Stairs* Dungeon::stair() const     //returns player
{
    return m_stairs;
}
bool Dungeon::addSnakewomen(int r, int c)       //qualifications for adding snakewoman
{
    if (!isPosInBounds(r, c))                   //must be in bounds
        return false;

    if (getCellStatus(r, c) != 0)
        return false;

    m_snakewomen[totalsnakewomen] = new Snakewomen(this, r, c);     //add snakewoman
    totalsnakewomen++;                                              //increment number of snakewomen
    return true;                                                       //return true if snakewoman can be added
}

bool Dungeon::addBogeymen(int r, int c) //same as addsnakewomen
{
    if (!isPosInBounds(r, c))
        return false;

    if (getCellStatus(r, c) != 0)
        return false;

    m_bogeymen[totalbogeymen] = new Bogeymen(this, r, c);
    totalbogeymen++;
    return true;
}

bool Dungeon::addDragons(int r, int c)      //same as addsnakewomen
{
    if (!isPosInBounds(r, c))
        return false;

    if (getCellStatus(r, c) != 0)
        return false;

    m_dragons[totaldragons] = new Dragons(this, r, c);
    totaldragons++;
    return true;
}

bool Dungeon::addGoblins(int r, int c)  //same as add snakewomen
{
    if (!isPosInBounds(r, c))
        return false;

    if (getCellStatus(r, c) != 0)
        return false;

    m_goblins[totalgoblins] = new Goblins(this, r, c);
    totalgoblins++;
    return true;
}

bool Dungeon::addPlayer(int r, int c)       //add player
{
    if (!isPosInBounds(r, c))
        return false;

    if (m_player != nullptr)        // don't add a player if one already exists
        return false;

    // Don't add a player on a spot not empty.... can player land on weapons and scrolls??
   // if (getCellStatus(r,c) == ' ')               //FIX THIS SUPPOSED TO BE != but not working
    //    return false;

    m_player = new Player(this, r, c);              //actually add player
    return true;
}

bool Dungeon::addStairs(int r, int c)       //add player
{
    if (!isPosInBounds(r, c))
        return false;

    if (m_stairs != nullptr)        // don't add a player if one already exists
        return false;

    // Don't add a player on a spot not empty.... can player land on weapons and scrolls??
   // if (getCellStatus(r,c) == ' ')               //FIX THIS SUPPOSED TO BE != but not working
    //    return false;

    m_stairs = new Stairs(this, r, c);              //actually add player
    return true;
}


void Dungeon::display(string msg) //const?
{
    char displayGrid[18][70];
    int r, c;

    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
        {
            if (getCellStatus(r, c) == 0)
                displayGrid[r - 1][c - 1] = '#';            // fill displayGrid with walls (#s)
        }
         
    for (int r = 2; r <= 17; r++)
    {
        for (int c = 2; c <= 69; c++)
            displayGrid[r - 1][c - 1] = ' ';        //create one large room
    }

    for (int k = 0; k < totalsnakewomen; k++) // indicate each snakewoman's position
    {
        const Monsters* sw = m_snakewomen[k];
        char& gridChar = displayGrid[sw->row() - 1][sw->col() - 1];
        if (gridChar == ' ')
            gridChar = 'S';
    }

    for (int k = 0; k < totalbogeymen; k++)     // indicate each bogeyman's position
    {
            const Monsters* b = m_bogeymen[k];
            char& gridChar = displayGrid[b->row() - 1][b->col() - 1];
            if (gridChar == ' ')
                gridChar = 'B';
    }
    
    for (int k = 0; k < totaldragons; k++)      //indicate each dragon's position
        {
            const Monsters* d = m_dragons[k];
            char& gridChar = displayGrid[d->row() - 1][d->col() - 1];
            if (gridChar == ' ')
                gridChar = 'D';
        }

    for (int k = 0; k < totalgoblins; k++)       // indicate each goblins's position
        {
            const Monsters* g = m_goblins[k];
            char& gridChar = displayGrid[g->row() - 1][g->col() - 1];
            if (gridChar == ' ')
                gridChar = 'G';
        }
    int rr = 7;
    int cc = 25;
    displayGrid[rr-1][cc-1] = ')';
    rr = 14;
    cc = 30;
    displayGrid[rr - 1][cc - 1] = ')';
    rr = 12;
    cc = 50;
    displayGrid[rr - 1][cc - 1] = '?';

    if (m_player != nullptr)            // indicate player's position
        displayGrid[m_player->row() - 1][m_player->col() - 1] = '@'; 


            if (msg != "leveldown") //for level 0, display stair
            {
                if (m_stairs != nullptr)
                {
                    if (m_level ==0 ||m_level == 1 || m_level == 2 || m_level == 3) //stairs on levels 0,1,2,3
                        displayGrid[m_stairs->row() - 1][m_stairs->col() - 1] = '>';
                    else if (m_level == 4)      //idol on level 4
                        displayGrid[m_stairs->row() - 1][m_stairs->col() - 1] = '&';
                }

                if (m_player->row() == m_stairs->row() && m_player->col() == m_stairs->col())   //if player and stairs on same spot
                {
                    displayGrid[m_stairs->row() - 1][m_stairs->col() - 1] = '@';            //show player on top
                }
            }
            else
            {
                    m_level++;          //every time > is pressed increment level
           
                    if (m_stairs != nullptr)
                        m_stairs->randomCoords(m_stairs->row(), m_stairs->col());

                    if (m_player != nullptr)
                        m_player->randomCoords(m_player->row(), m_player->col()); //create random coords for player on next level

                    for (int k = totalsnakewomen - 1; k >= 0; k--)  //delete snakewomen
                    {
                        Snakewomen* sw = m_snakewomen[k];
                        delete sw;
                        m_snakewomen[k] = m_snakewomen[totalsnakewomen - 1];
                        totalsnakewomen--;
                    }
                   

                    int sw = 0;                                 //populate w snakewomen
                    if (m_level == 1) //level 1
                        sw = randInt(1, 5);
                    else if (m_level == 2) //level 2
                        sw = randInt(1, 5);
                    else if (m_level == 3) //level 3
                        sw = randInt(0, 6);
                    else if (m_level == 4) //level 4
                        sw = randInt(1, 6);

                    for (int p = 0; p < sw; p++)
                    {
                        int r = randInt(2, 17);
                        int c = randInt(2, 69);
                        if (r == m_player->row() && c == m_player->col())       //if on player, don't add snakewoman
                            continue;
                        addSnakewomen(r, c);
                    }

                    for (int k = totalbogeymen - 1; k >= 0; k--)        //delete bogeymen
                    {
                        Monsters* b = m_bogeymen[k];
                        delete b;
                        m_bogeymen[k] = m_bogeymen[totalbogeymen - 1];
                        totalbogeymen--;
                    }

                    int bg = 0;                                         //add bogeymen
                    if (m_level == 1) // not on level 0,1
                        bg = 0;
                    else if (m_level == 2) //level 2
                        bg = randInt(1, 5);
                    else if (m_level == 3) //level 3
                        bg = randInt(1, 5);
                    else if (m_level == 4) //level 4
                        bg = randInt(0, 7);
                    for (int p = 0; p < bg; p++)
                    {
                        int r = randInt(2, 17);
                        int c = randInt(2, 69);
                        if (r == m_player->row() && c == m_player->col())
                            continue;
                        addBogeymen(r, c);
                    }

                    for (int k = totaldragons - 1; k >= 0; k--)         //delete dragons
                    {
                        Monsters* d = m_dragons[k];
                        delete d;
                        m_dragons[k] = m_dragons[totaldragons - 1];
                        totaldragons--;
                    }

                    int d = 0;                                                          //add dragons
                    if (m_level == 1 || m_level == 2) // not on level 0,1,2
                        d = 0;
                    else if (m_level == 3) //level 3
                        d = randInt(1, 5);
                    else if (m_level == 4) //level 4
                        d = randInt(0, 7);
                    for (int p = 0; p < d; p++)
                    {
                        int r = randInt(2, 17);
                        int c = randInt(2, 69);
                        if (r == m_player->row() && c == m_player->col())
                            continue;
                        addDragons(r, c);
                    }

                    for (int k = totalgoblins - 1; k >= 0; k--)     //delete goblins
                    {
                        Monsters* g = m_goblins[k];
                        delete g;
                        m_goblins[k] = m_goblins[totalgoblins - 1];
                        totalgoblins--;
                    }

                    int g = 0;                                  //add goblins
                    if (m_level == 1)//level 1
                        g = randInt(1, 6);
                    else if (m_level == 2)//level 2
                        g = randInt(0, 6);
                    else if (m_level == 3) //level 3
                        g = randInt(0, 5);
                    else if (m_level == 4) //level 4
                        g = randInt(1, 6);
                    for (int p = 0; p < g; p++)
                    {
                        int r = randInt(2, 17);
                        int c = randInt(2, 69);
                        if (r == m_player->row() && c == m_player->col())
                            continue;
                        addGoblins(r, c);
                    }
                 
            }
 
            if (m_level >= 5)           //level cannot be number greater than 4
            {
                clearScreen();
                cout << "Error: no level lower than 4." << endl;    //error message
                cout << "Press q to exit game.";
                return;
            }
           
    clearScreen();

    for (r = 1; r <= rows(); r++)       //display grid
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    //display updated hitpoints, level, etc.
        cout << "Dungeon Level: " << m_level << ", Hit points: " << m_player->hitpoints() << ", Armor: " << m_player->armor() << ", Strength: " << m_player->strength() << ", Dexterity: " << m_player->dexterity() << endl;
        cout << endl;
        
        if (attack() == "goblins" || attack() == "dragons" || attack() == "snakewomen" || attack() == "bogeymen") //if player attacks
            cout << "Player attacks " << endl;
       
        
        for (int k = 0; k < totalgoblins; k++)  
        {
            Monsters* g = m_goblins[k];
            if(attack() == "goblins")                          //if goblin is next to player
            {
                if (dexterityProbability() == "hits.") 
                {
                    m_player->getAttacked();                     //player gets attacked
                    cout << "the Goblin slashes short sword at Player and " << "hits." << endl;           //if goblin attacks
                }
                else {
                    cout << "the Goblin slashes short sword at Player and " << "misses." << endl;

                }
                

                m_goblins[k]->getAttacked();                //and goblin gets attacked
                dieGoblins();                              //move goblins accordingly/delete if they die
                break;
            }
        }
        for (int k = 0; k < totaldragons; k++)  //dragon attacks
        {
            Monsters* g = m_dragons[k];
            if (attack() == "dragons")
            {

                cout << "the Dragon swings long sword at Player and " << endl;
                m_player->getAttacked();
                m_dragons[k]->getAttacked();
                dieDragons();
                break;
            }
        }
        for (int k = 0; k < totalsnakewomen; k++)  // snakewoman attacks
        {
            Snakewomen* g = m_snakewomen[k];
            if (attack() == "snakewomen")
            {
                cout << "the Snakewoman strikes magic fangs at Player and " << endl;
                m_player->getAttacked();
                m_snakewomen[k]->getAttacked();
                dieSnakewomen();
                break;
            }
        }
        for (int k = 0; k < totalbogeymen; k++)  //bogeyman attacks
        {
            Monsters* g = m_bogeymen[k];
            if (attack() == "bogeymen")
            {
                cout << "the Bogeyman chops magic axe at Player and " << endl;
                m_player->getAttacked();
                m_bogeymen[k]->getAttacked();
               // moveBogeymen();
                dieBogeymen();
                break;
            }
        }
        
        if (m_player->isDead())     //if player is dead, exit game
        {
            cout << "Press q to exit the game.";
            exit(1);        //so player cannot do anything else
        }
}

bool Dungeon::determineNewPosition(int& r, int& c, int dir) const       //return false if player hits a wall
{
    for (int k = 0; k < totalgoblins; k++)  // for every goblin, make sure player cannot go on space
    {
        Monsters* g = m_goblins[k];
        switch (dir)
        {
        case ARROW_UP:
            if (r <= 2 || (r - 2 == g->row() - 1 && c == g->col()))
                return false;
            break;
        case ARROW_DOWN:
            if (r >= rows() - 1 || (r == g->row() - 1 && c == g->col()))
                return false;
            break;
        case ARROW_LEFT:
            if (c <= 2 || (r == g->row() && c - 2 == g->col() - 1))
                return false;
            break;
        case ARROW_RIGHT:
            if (c >= cols() - 1 || (r == g->row() && c == g->col() - 1))
                return false;
            break;
        default:     return false;
        }
    }
    for (int k = 0; k < totalsnakewomen; k++)  // for every snakewoman, make sure player cannot go on space
    {
        Monsters* sw = m_snakewomen[k];
        switch (dir)
        {
        case ARROW_UP:
            if (r <= 2 || (r - 2 == sw->row() - 1 && c == sw->col()))
                return false;
            break;
        case ARROW_DOWN:
            if (r >= rows() - 1 || (r == sw->row() - 1 && c == sw->col()))
                return false;
            break;
        case ARROW_LEFT:
            if (c <= 2 || (r == sw->row() && c - 2 == sw->col() - 1))
                return false;
            break;
        case ARROW_RIGHT:
            if (c >= cols() - 1 || (r == sw->row() && c == sw->col() - 1))
                return false;
            break;
        default:     return false;
        }
    }

           for (int k = 0; k < totaldragons; k++)  // for every dragon, make sure player cannot go on space
            {
                Monsters* d = m_dragons[k];
                switch (dir)
                {
                case ARROW_UP:
                    if (r <= 2 || (r - 2 == d->row() - 1 && c == d->col()))
                        return false;
                    break;
                case ARROW_DOWN:
                    if (r >= rows() - 1 || (r == d->row() - 1 && c == d->col()))
                        return false;
                    break;
                case ARROW_LEFT:
                    if (c <= 2 || (r == d->row() && c - 2 == d->col() - 1))
                        return false;
                    break;
                case ARROW_RIGHT:
                    if (c >= cols() - 1 || (r == d->row() && c == d->col() - 1))
                        return false;
                    break;
                default:     return false;
                }
            }

           //monsters cannot move onto player
           switch (dir)
           {
           case ARROW_UP:
               if (r <= 2 || (r - 2 == m_player->row() - 1 && c == m_player->col()))
                   return false;
               break;
           case ARROW_DOWN:
               if (r >= rows() - 1 || (r == m_player->row() - 1 && c == m_player->col()))
                   return false;
               break;
           case ARROW_LEFT:
               if (c <= 2 || (r == m_player->row() && c - 2 == m_player->col() - 1))
                   return false;
               break;
           case ARROW_RIGHT:
               if (c >= cols() - 1 || (r == m_player->row() && c == m_player->col() - 1))
                   return false;
               break;
           default:     return false;
           }

            for (int k = 0; k < totalbogeymen; k++)  // for every bogeymen, make sure player cannot go on space
            {
                Monsters* b = m_bogeymen[k];
                switch (dir)
                {
                case ARROW_UP:
                    if (r <= 2 || (r - 2 == b->row() - 1 && c == b->col()))
                        return false;
                    break;
                case ARROW_DOWN:
                    if (r >= rows() - 1 || (r == b->row() - 1 && c == b->col()))
                        return false;
                    break;
                case ARROW_LEFT:
                    if (c <= 2 || (r == b->row() && c - 2 == b->col() - 1))
                        return false;
                    break;
                case ARROW_RIGHT:
                    if (c >= cols() - 1 || (r == b->row() && c == b->col() - 1))
                        return false;
                    break;
                default:     return false;
                }
              }

        if (dir == ARROW_UP)    //if player can move, move player in appropriate direction
            r--;
        if (dir == ARROW_DOWN)
            r++;
        if (dir == ARROW_LEFT)
            c--;
        if (dir == ARROW_RIGHT)
            c++;
      return true;
}

void Dungeon::moveSnakewomen() //if next to player, follow player, else: move randomly
{
    for (int k = totalsnakewomen - 1; k >= 0; k--)
    {
        Monsters* sw = m_snakewomen[k];
       if ((sw->col() == m_player->col() - 2 && (sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1 || sw->row() == m_player->row() + 2))
            || (sw->col() == m_player->col() - 3 && (sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1))
            || (sw->col() == m_player->col() - 4 && sw->row() == m_player->row()))
        {
            int dir = ARROW_RIGHT;
            sw->follow(dir);
        }
        
        else if((sw->col() == m_player->col() && (sw->row() == m_player->row() - 2 || sw->row() == m_player->row() - 1 || sw->row() == m_player->row() - 3 ))
            || (sw->col() -1== m_player->col() - 2 && sw->row() == m_player->row() - 2)
            || (sw->col() == m_player->col() + 1 && sw->row() == m_player->row() - 2))
        {
            int dir = ARROW_DOWN;
                sw->follow(dir);
        }
        
        else if ((sw->col() == m_player->col() && (sw->row() == m_player->row() + 1 || sw->row() == m_player->row() + 2 || sw->row() == m_player->row() + 3))
            || (sw->col() - 1 == m_player->col() - 2 && sw->row() == m_player->row() + 2)
            || (sw->col() == m_player->col() + 1 && sw->row() == m_player->row() + 2))
        {
            int dir = ARROW_UP;
            sw->follow(dir);
        }
        
        else if ((sw->col() == m_player->col() + 2 && ( sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1 || sw->row() == m_player->row() + 2))
            || (sw->col() == m_player->col() +3 && (sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1))
            || (sw->col() == m_player->col() +4 && sw->row() == m_player->row()))
        {
            int dir = ARROW_LEFT;
            sw->follow(dir);
        }
        
        else
        sw->move();     //if not next to player, move randomly

    }
}

 void Dungeon::moveBogeymen()
{
    // move all bogeymen
    for (int k = totalbogeymen - 1; k >= 0; k--)
    {
        
        Monsters* sw = m_bogeymen[k]; 
        if ((sw->col() == m_player->col() - 2 && (sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1 || sw->row() == m_player->row() + 2))
            || (sw->col() == m_player->col() - 3 && (sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1))
            || (sw->col() == m_player->col() - 4 && sw->row() == m_player->row()))
        {
            int dir = ARROW_RIGHT;
            sw->follow(dir);
           
        }
        
         if ((sw->col() == m_player->col() && (sw->row() == m_player->row() - 2 || sw->row() == m_player->row() - 1 || sw->row() == m_player->row() - 3))
            || (sw->col() - 1 == m_player->col() - 2 && sw->row() == m_player->row() - 2) || (sw->col() == m_player->col() + 1 && sw->row() == m_player->row() - 2)
            )
        {
            int dir = ARROW_DOWN;
            sw->follow(dir);
           
        }

        
         if ((sw->col() == m_player->col() && (sw->row() == m_player->row() + 1 || sw->row() == m_player->row() + 2 || sw->row() == m_player->row() + 3 || sw->row() == m_player->row() + 4  || sw->row() == m_player->row() + 5))
            || (sw->col() - 1 == m_player->col() - 2 && sw->row() == m_player->row() + 2) || (sw->col() == m_player->col() + 1 && sw->row() == m_player->row() + 2 )
            )
        {
            int dir = ARROW_UP;
            sw->follow(dir);
           
        }

        /*
         if ((sw->col() == m_player->col() + 2 && (sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1 || sw->row() == m_player->row() + 2))
            || (sw->col() == m_player->col() + 3 && (sw->row() == m_player->row() - 1 || sw->row() == m_player->row() || sw->row() == m_player->row() + 1))
            || (sw->col() == m_player->col() + 4 && sw->row() == m_player->row()))
        {
            int dir = ARROW_LEFT;
            sw->follow(dir);
           
        }
        */
    }
}
string Dungeon::attack()
{
    for (int k = 0; k < totalgoblins; k++)  //if player is next to goblin
    {
        Monsters* g = m_goblins[k];
        if ((m_player->row() - 2 == g->row() - 1 && m_player->col() == g->col()) || (m_player->row() == g->row() - 1 && m_player->col() == g->col())
            || (m_player->row() == g->row() && m_player->col() - 2 == g->col() - 1) || (m_player->row() == g->row() && m_player->col() == g->col() - 1))
            return "goblins";
    }

    for (int k = 0; k < totalsnakewomen; k++)  // if player is next to snakewoman
    {
        Monsters* g = m_snakewomen[k];
        if ((m_player->row() - 2 == g->row() - 1 && m_player->col() == g->col()) || (m_player->row() == g->row() - 1 && m_player->col() == g->col())
            || (m_player->row() == g->row() && m_player->col() - 2 == g->col() - 1) || (m_player->row() == g->row() && m_player->col() == g->col() - 1))
            return "snakewomen";
    }

    for (int k = 0; k < totaldragons; k++)  // if player is next to dragon
    {
        Monsters* g = m_dragons[k];
        if ((m_player->row() - 2 == g->row() - 1 && m_player->col() == g->col()) || (m_player->row() == g->row() - 1 && m_player->col() == g->col())
            || (m_player->row() == g->row() && m_player->col() - 2 == g->col() - 1) || (m_player->row() == g->row() && m_player->col() == g->col() - 1))
            return "dragons";
    }

    for (int k = 0; k < totalbogeymen; k++)  // if player is next to bogeyman
    {
        Monsters* g = m_bogeymen[k];
        if ((m_player->row() - 2 == g->row() - 1 && m_player->col() == g->col()) || (m_player->row() == g->row() - 1 && m_player->col() == g->col())
            || (m_player->row() == g->row() && m_player->col() - 2 == g->col() - 1) || (m_player->row() == g->row() && m_player->col() == g->col() - 1))
            return "bogeymen";
    }
    
            return "";  //else player not next to any monste
}

void Dungeon::dieGoblins() //delete all snakewomen
{
    for (int k = totalgoblins - 1; k >= 0; k--)
    {
        Monsters* g = m_goblins[k];
        if (g->isDead())
        {
            delete g;
            m_goblins[k] = m_goblins[totalgoblins - 1];
            totalgoblins--;
        }
    }
}

void Dungeon::dieSnakewomen()   //delete all snakewomen
{
    for (int k = totalsnakewomen - 1; k >= 0; k--)
    {
        Snakewomen* g = m_snakewomen[k];
        if (g->isDead())
        {
            delete g;
            m_snakewomen[k] = m_snakewomen[totalsnakewomen - 1];
            totalsnakewomen--;
        }
    }
}

void Dungeon::dieDragons()      //kill off all dragons
{
    for (int k = totaldragons - 1; k >= 0; k--)
    {
        Monsters* g = m_dragons[k];
        if (g->isDead())
        {
            delete g;
            m_dragons[k] = m_dragons[totaldragons - 1];
            totaldragons--;
        }
    }
}

void Dungeon::dieBogeymen()
{
    for (int k = totalbogeymen - 1; k >= 0; k--)
    {
        Monsters* g = m_bogeymen[k];
        if (g->isDead())
        {
            delete g;
            m_bogeymen[k] = m_bogeymen[totalbogeymen - 1];
            totalbogeymen--;
        }
    }
}

string Dungeon::dexterityProbability()   //added bc dexterity bonus wasn't working
{
    if (trueWithProbability(0.5))       //bc dexterity wasn't working
        return "hits.";
    else
        return "misses.";
}


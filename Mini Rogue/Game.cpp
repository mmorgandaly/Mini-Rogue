// Game.cpp

#include "Game.h"
#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"
#include "Monsters.h"
#include "Objects.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    m_dungeon = new Dungeon(18, 70);


    // add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(2, 17);
        cPlayer = randInt(2, 69);
    } while (m_dungeon->getCellStatus(rPlayer, cPlayer) != 0);
    m_dungeon->addPlayer(rPlayer, cPlayer);

   //add snakewomen
   int sw = randInt(1, 3);
   for (int p = 0; p < sw; p++)
    {
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        if (r == rPlayer && c == cPlayer) //don't add if lands on player
            continue;
        m_dungeon->addSnakewomen(r, c);
    }
  
       //add goblins
       int g =randInt(1, 3);
       for (int p = 0; p < g; p++)
       {

           int r = randInt(2, 17);
           int c = randInt(2, 69);
           if (r == rPlayer && c == cPlayer)
               continue;
           m_dungeon->addGoblins(r, c);
       }  

       //add stairs
       int rs = randInt(2, 17);
       int cs = randInt(2, 69);
       m_dungeon->addStairs(rs, cs);
}
Game::~Game()   //destructor
{
    delete m_dungeon;
}

void Game::play()
{
    m_dungeon->display(""); //display dungeon
    Player* player = m_dungeon->player();
    Stairs* stair = m_dungeon->stair();
    if (player == nullptr)  //player cannot be nullptr
        return;
    char dir;
    while (true)    //taking a turn
    {
     
        if (trueWithProbability(0.1) && player->maxhp() > player->hitpoints()) // 1/10 chance player will inc hp (up to max hp) every time command is pressed
            player->increaseHP();
            
        switch (getCharacter())
        {
        case 'h':       //move left
            dir = ARROW_LEFT;
            player->move(dir);          //move player left
            m_dungeon->display("");
            m_dungeon->moveSnakewomen();        //snakewomen move randomly
            m_dungeon->display("");
            m_dungeon->moveBogeymen();        //bogeymen move
            m_dungeon->display("");
            break;
        case 'l':       //move right
            dir = ARROW_RIGHT;
            player->move(dir);
            m_dungeon->display("");
            m_dungeon->moveSnakewomen();        //snakewomen move randomly
            m_dungeon->display("");
            m_dungeon->moveBogeymen();        //bogeymen move
            m_dungeon->display("");
            break;
        case 'j':       //move down
            dir = ARROW_DOWN;
            player->move(dir);
            m_dungeon->display("");
            m_dungeon->moveSnakewomen();        //snakewomen move randomly
            m_dungeon->display("");
            m_dungeon->moveBogeymen();        //bogeymen move
            m_dungeon->display("");
            break;
        case 'k':        //move up
            dir = ARROW_UP;
            player->move(dir);
            m_dungeon->display("");
            m_dungeon->moveSnakewomen();        //snakewomen move randomly
            m_dungeon->display("");
            m_dungeon->moveBogeymen();        //bogeymen move
            m_dungeon->display("");
            break;
        case'i':        //look at inventory
            player->showInventory();
            break;
        case '>':       //go down stairs when on staircase
           if (m_dungeon->level() < 4) //stairs from level 0 to 3
            {
                if (player->row() == stair->row() && player->col() == stair->col())
                {
                    m_dungeon->display("leveldown");
                    m_dungeon->display("");
                }
            }
            break;
        case 'c':       //cheat
            player->cheat();
            break;
            case 'g':       //pick up item by standing on it
                if ((player->row() == stair->row() && player->col() == stair->col()) && m_dungeon->level() == 4) //if player on golden idol
                {
                    cout << "Congratulations, you won!" << endl;    //player wins
                    cout << "Press q to exit game." << endl;        //exit game
                }
                break;
            /*
            case 'w':          //wield weapon and select from inventory
                break;
            case 'r':   //read scroll then select scroll from inventory
                break; */
            case'q':
                exit(1);
            break;
        default:       //only monsters take turn if any other key is pressed
            m_dungeon->moveSnakewomen();        //snakewomen move randomly
            m_dungeon->display("");
            m_dungeon->moveBogeymen();          //bogeymen move if by player
            m_dungeon->display("");
            break;
        }
    }
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Bogeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

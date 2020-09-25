#ifndef DUNGEON_H
#define DUNGEON_H

#include <string>
using namespace std;

class Player;
class Snakewomen;
class Bogeymen;
class Dragons;
class Goblins;
class Stairs;


class Dungeon
{
public:
    Dungeon(int nRows, int nCols);
    ~Dungeon();

    int rows() const;
    int cols() const;
    int level() const;
    Player* player() const;
    Stairs* stair() const;
    int getCellStatus(int r, int c) const;
    void     display(std::string msg) ;
    bool determineNewPosition(int& r, int& c, int dir) const;
   void setCellStatus(int r, int c, int status);
   string attack();
   string dexterityProbability();   


   bool addStairs(int r, int c);
   bool addPlayer(int r, int c);
   bool addSnakewomen(int r, int c);
   void moveSnakewomen();
   void dieSnakewomen();
   bool addBogeymen(int r, int c);
   void moveBogeymen();
   void dieBogeymen();
   bool addDragons(int r, int c);
   void dieDragons();
   bool addGoblins(int r, int c);
   void dieGoblins();
  
private:
    int      m_grid[18][70];
    int      m_rows;
    int      m_cols;
    int      m_turns;
    int m_level;      //levels 0 to 4

    Stairs* m_stairs;
    Player* m_player;
    Snakewomen* m_snakewomen[6];        //max = 6 per level
    int      totalsnakewomen;
    Bogeymen* m_bogeymen[7];        //max = 7 per level
    int      totalbogeymen;
    Dragons* m_dragons[7];        //max = 7 per level
    int      totaldragons;
    Goblins* m_goblins[6];        //max = 6 per level
    int      totalgoblins;

    void checkPos(int r, int c, std::string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

#endif // DUNGEON_H

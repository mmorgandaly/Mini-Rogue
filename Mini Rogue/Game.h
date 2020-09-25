// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class Dungeon;
// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
private:
    Dungeon* m_dungeon;
};

#endif // GAME_INCLUDED

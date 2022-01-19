#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H
#include <string>

using namespace std;

class Player
{
    public:
    Player();
    Player(string playerNameIn, bool isPartyLeaderIn,bool isDeadIn);
    string getPlayerName();
    void setPlayerName(string playerNameIn);
    bool getIsLeader();
    void setIsLeader(bool isPartyLeaderIn);
    bool getIsDead();
    void setIsDead(bool isDeadIn);

    private:
    string playerName;
    bool isDead;
    bool isPartyLeader;
};

#endif
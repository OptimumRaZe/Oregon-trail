#include <iostream>
#include <string>
#include "playerClass.h"

Player::Player()
{
    playerName="";
    isDead=true;
    isPartyLeader=false;
}
Player::Player(string playerNameIn,bool isPartyLeaderIn,bool isDeadIn)
{
    playerName=playerNameIn;
    isDead=false;
    isPartyLeader=isPartyLeaderIn;
}
string Player::getPlayerName()
{
    return playerName;
}
void Player::setPlayerName(string playerNameIn)
{
    playerName=playerNameIn;
}
bool Player::getIsLeader()
{
    return isPartyLeader;
}
void Player::setIsLeader(bool isPartyLeaderIn)
{
    isPartyLeader=isPartyLeaderIn;
}
bool Player::getIsDead()
{
    return isDead;
}
void Player::setIsDead(bool isDeadIn)
{
    isDead=isDeadIn;
}
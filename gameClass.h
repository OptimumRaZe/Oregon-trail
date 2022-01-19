// CS1300 Fall 2020
// Author: Freddy Perez
// Recitation: 324 Michael Hoefer
// Project 3  - Problem # 1
#ifndef GAMECLASS_H
#define GAMECLASS_H
#include <string>
#include "dateClass.H"
#include "playerClass.h"
#include "milestonesClass.h"

using namespace std;

class Game
{
    public:
    Game();
    Game(Date date, Player players[],Milestone milestones[]);
    int getAlivePlayers();
    void setAlivePlayer(int playersAliveIn);
    double getMoney();
    void setMoney(double moneyIn);
    int getMilage();
    int getFood();
    void setFood(int foodIn);
    int getAmmo();
    void setAmmo(int ammoIn);
    int getOxen();
    void setOxen(int oxenIn);
    string getNamePlayers();
    int getWagon();
    int getMedical();
    void setWagon(int wagonIn);
    void setMedical(int medicalIn);
    void setMilage(int milesIn);
    Milestone nextMile(int milestonePos);
    void getDate();
    void setDate(Date dateIn);
    void startingStoreBuy();
    void fortStoreBuy(double priceIncreaseIn);
    int getYokes();
    void setYokes(int yokesIn);
    bool isGameOver();
    void setGameOver(bool gameoverIn);
    void hunt();
    void rest();
    int continueTrip(int milestonePos);
    void misfortune();
    void updateDayMonth(int daysPast);
    void raiderAttack();
    void gameOver();
    void statusUpdate(int playerTurn,int milestonePos);

    private:
    Player players[5];
    int numPlayersAlive;
    Milestone milestones[16];
    double money;
    Date date;
    int poundsFood;
    int ammunition;
    int numOxen;
    int wagonParts;
    int medicalSup;
    int milage;
    int totalYokes;
    bool gameOverBool;
    int daysPast;
};

#endif
// CS1300 Fall 2020
// Author: Freddy Perez
// Recitation: 324 Michael Hoefer
// Project 3  - Problem # 2
#include <iostream>
#include <string>
#include <fstream>
#include "storeClass.h"
#include "milestonesClass.h"
#include "gameClass.h"
#include "dateClass.H"
#include "playerClass.h"

using namespace std;

int split(string input,char seperator,string arr[])
{
    int stringlength=input.length();
    int pos =0;
    int endingPos=0;
    int k=0;
    if (input=="")
    { 
        return 0;
    }
    else
    {
         for (int i=0;i< stringlength;i++)  // traversing input
        {
            endingPos=i-pos;       // setting length of substring
            if (input[i]==seperator)     // if char is the same as seperator
            {
                arr[k]=input.substr(pos,endingPos);    //setting array value to substring from input
                pos=i+1;   // starting position of substring
                k++;       //array position gets incrimented
            }
        }
        arr[k]=input.substr(pos,stringlength);   // last substring of input
        return k+1;
    }
}
bool checkDate(string dates[])
{
    string date;
    bool invalidDate=true;
    cout << "When would you like to start the journey? (mm/dd)\nDefault is 03/28/1847. Range must be between 03/01/1847 & 05/01/1847."<< endl;
    while (invalidDate==true)
    {
        cin >> date;
        if (split(date,'/',dates)!=2)
        {
            cout << "Please enter a valid date." << endl;
        }
        else
        {
            if (dates[0]=="" || dates[1]=="")
            {
                cout << "Please enter a valid date." << endl;
            }
            else
            {
                int month=stoi(dates[0]);
                int day=stoi(dates[1]);
                if (month==3 && day >0 && day < 32)
                {
                    invalidDate=false;
                }
                else if (month==4 && day >0 && day < 31)
                {
                    invalidDate=false;
                }
                else if (month==5 && day == 1)
                {
                    invalidDate=false;
                }
                else
                {
                    cout << "Please enter a valid date." << endl;
                }
            } 
        }
    }
    return invalidDate;
}
void readFile(Milestone milestones[],Store stores[])
{
    string line,milestoneName;
    int miles;
    double priceIncrease=0;
    ifstream file;
    int i=0,j=0;
    file.open("milestones.txt");
    if (file.is_open())
    {
        while (getline(file,line))
        {
            if (isalpha(line[0]))
            {
                milestoneName=line;
                milestones[i].setMilestoneName(milestoneName);
                if (milestoneName[0]=='F')
                {
                    milestones[i].setisFort(true);
                    priceIncrease=priceIncrease+0.25;
                    stores[j].setPriceIncrease(priceIncrease);
                    stores[j].setStoreName(milestoneName);
                    j++;
                }
            }
            if (isdigit(line[0]))
            {
                miles=stoi(line);
                milestones[i].setMilestoneMilage(miles);
                i++;
            }
        }
    }
    file.close();
}
void getPlayers(Player players[])
{
    string playerNameIn;
    cout << "Please enter the name of the leader of your group." << endl;
    cin >> playerNameIn;
    Player leader=Player(playerNameIn,true,false);
    players[0]=leader;
    cout << "Awesome! Glad you could make the trip, " << playerNameIn << "!"<< endl; 
    cout << "Please enter the names of the other four travelers with you. (Followed by enter after each name)" << endl;
    cin >> playerNameIn;
    Player player1=Player(playerNameIn,false,false);                       //Takes in player info
    players[1]=player1;
    cin >> playerNameIn;
    Player player2=Player(playerNameIn,false,false);
    players[2]=player2;
    cin >> playerNameIn;
    Player player3=Player(playerNameIn,false,false);
    players[3]=player3;
    cin >> playerNameIn;
    Player player4=Player(playerNameIn,false,false);
    players[4]=player4;
}
void intro(Milestone milestones[], Store stores[], Player players[],string dates[])
{
    readFile(milestones,stores);
    cout << "Hello! Welcome to the Oregon Trail game, Text edition." << endl;
    cout << "=====================================================================" << endl;
    cout << "The goal is to travel from Independence, Missouri to Oregon City (2040 miles) by the end of\nfall (November 30th, 1847). However, the trail is arduous. Each day costs you food and has risks.\nYou can hunt and rest, but you have to get there before winter!" << endl;
    cout << "=====================================================================" << endl;
    getPlayers(players);
    cout << "Nice crew you got there!" << endl;
    checkDate(dates);
}
int main()
{   
    double priceIncrease=0;
    int turnInput,fortInput;
    string playerNameIn, dates[2];
    Milestone milestones[16];
    Player players[5];
    Store stores[6];
    Date DATE;

    intro(milestones,stores,players,dates);                             //BEGINNING OF GAME          

    int month=stoi(dates[0]);
    DATE.setMonth(month);
    int day=stoi(dates[1]);
    DATE.setDay(day);

    cout << "Great! You're scheduled to leave on, ";
    switch (month)
    {
        case 3: cout << "March " << day << "." << endl;break;
        case 4: cout << "April " << day << "." << endl;break;                    //Sets starting date
        case 5: cout << "May first." << endl;break;
        default: cout << "CONGRATS YOU BROKE MY GAME!" << endl;break;
    }                            
////////////////////////////////CREATING GAME WITH STARTING DATE, LIST OF PLAYERS AND LIST OF MILESTONES
    Game oregonTrail=Game(DATE,players,milestones); 
    oregonTrail.startingStoreBuy(); //Inital store
    
//////////////////////////TURNS
    int milestonePos=0;
    int storePos=0;
    for (int i=0;i<5;i++)
    {
        if (oregonTrail.isGameOver()==true)
        {
            oregonTrail.gameOver();                                     //GAME OVER
            break;
        }
        else if (players[0].getIsDead()==true)
        {
            cout << "Party leader is dead." << endl;
            oregonTrail.setGameOver(true);                                  //LEADER DEAD
        }
        else if(oregonTrail.getOxen()<1)
        {
            cout << "All oxen have died." << endl;                          //OXEN DEAD
            oregonTrail.setGameOver(true);
        }
        else if (oregonTrail.getFood()<1)
        {
            cout << "You have no food left!" << endl;
            oregonTrail.setGameOver(true);                              //NO FOOD
        }
        else if(players[i].getIsDead()!=true)
        {
            oregonTrail.statusUpdate(i,milestonePos);                                    //STATUS UPDATE
            if (milestones[milestonePos-1].getisFort()==true && oregonTrail.getMilage()==milestones[milestonePos-1].getmilestoneMilage())
            {
                priceIncrease=stores[storePos].getPriceIncrease();
                storePos++;
                cout << "Hello you've arrived at a fort. Would you like to:\n1. Rest\n2. Shop\n3. Continue journey" << endl;                //AT FORT
                cin >> fortInput; 
                while (fortInput!=3)
                {
                    while (fortInput!=1 && fortInput !=2)
                    {
                        cout << "Invalid option. Please try again." << endl;
                        cin >> fortInput;break;
                    }
                    if (fortInput==1 || fortInput==2)
                    {
                        switch (fortInput)
                        {
                            case 1: oregonTrail.rest();break;               //rest
                            case 2: oregonTrail.fortStoreBuy(priceIncrease);break;          //shop
                        }
                        cout << "Would you like to:\n1. Rest\n2. Shop\n3. Continue journey" << endl;
                        cin >> fortInput;
                    }
                }
                if (fortInput==3)
                {
                    turnInput=2;
                }
            }
            else
            {
                cout << "\nWhat would you like to do?\n1. Stop to rest\n2. Continue\n3. Hunt\n4. Quit" << endl;
                cin >> turnInput;
            }
            
            while (turnInput!=1 && turnInput!=2 && turnInput!=3 && turnInput!=4)
            {
                cout << "Invalid option, try again." << endl;
                cin>> turnInput;
            }
            switch (turnInput)
            {
                case 1: oregonTrail.rest();                         //rest
                oregonTrail.misfortune();
                oregonTrail.raiderAttack();
                break;

                case 2: milestonePos=oregonTrail.continueTrip(milestonePos);                    //continue
                oregonTrail.misfortune();
                oregonTrail.raiderAttack();
                break;

                case 3:                                                 //hunt
                oregonTrail.hunt();
                oregonTrail.misfortune();
                oregonTrail.raiderAttack();
                break;

                case 4: cout << "We're sorry you had to cut your trip short." << endl;
                oregonTrail.setGameOver(true);break;                                           //quit
            }
        }
        else if (players[i].getIsDead()==true)
        {
            cout<<"Sorry! Player: "<< players[i].getPlayerName()<< " is dead, next player!" << endl;                //NEXT PLAYER CAUSE THAT ONES DEAD
            if (i==4)
            {
                i=-1;                   //RESTART LOOP
            }
        } 
        if (i==4)
        {           
            i=-1;           //RESTART LOOP
        } 
    }
}
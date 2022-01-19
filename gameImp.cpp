#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include "storeClass.h"
#include "gameClass.h"
#include "dateClass.H"


Game::Game()
{
    money=0;
    numPlayersAlive=0;
    date=Date();
    poundsFood=0;
    ammunition=0;
    milage=0;
    numOxen=0;
    wagonParts=0;
    medicalSup=0;
}
Game::Game(Date dateIn, Player playersIn[], Milestone milestonesIn[])
{
    numPlayersAlive=5;
    date=dateIn;
    for (int i=0;i<5;i++)
    {
        players[i]=playersIn[i];
    }
    for (int j=0;j<16;j++)
    {
        milestones[j]=milestonesIn[j];
    }
    totalYokes=0;
    medicalSup=0;
    poundsFood=0;
    wagonParts=0;
    ammunition=0;
    money=1600;
    numOxen=0;
    milage=0;
    gameOverBool=false;
}
void Game::setDate(Date dateIn)
{
    date=dateIn;
}
int Game::getYokes()
{
    return totalYokes;
}
void Game::setYokes(int yokesIn)
{
    totalYokes=yokesIn;
}
void Game::fortStoreBuy(double priceIncreaseIn)
{
    int yokesIn=0,foodIn=0,ammoIn=0,partsIn=0,medicalIn=0;
    double billSoFar=0;
    int buyingInput;
    string date,Oxen="Oxen",Bullets="Bullets",Wagon="Wagon",Medical="Medical",Food="Food";
    Store store=Store("FortStore",priceIncreaseIn);
    cout << "Hello! You've arrived at a fort!\n" << endl;
    cout << "==============================\nWelcome to the Fort Store\n==============================" << endl;
    cout << "You have: $" << money << " to spend." << endl;
    cout << endl;
    cout << "What would you like to purchase: (Numeric value)" << endl;
    cout << "1.Oxen\n2.Food\n3.Bullets\n4.Miscellaneous Supplies\n5.Exit store" << endl;
    cin >> buyingInput;
    while (buyingInput!=5)
    {
        switch (buyingInput)
        {                           //buying process
            case 1:
            cout << "How many yokes would you like to purchase?" << endl;
            cout << "Total yokes so far: " << totalYokes << endl;
            cin >> yokesIn;
            while (yokesIn*(40+(40*priceIncreaseIn))>money || billSoFar>money || yokesIn>5 || totalYokes+yokesIn>5 || store.Buy(Bullets,ammoIn,money,priceIncreaseIn)>money)            //oxen
            {
                if (yokesIn*(40+(40*priceIncreaseIn))>money || billSoFar>money)
                {
                    cout << "You do not have sufficient money" << endl;
                    cin >> yokesIn;
                }
                else if (yokesIn>5 || totalYokes+yokesIn>5)
                {
                    cout << "Cannot exceed 5 yokes of oxen." << endl;
                    cin >> yokesIn;
                }
            }
            if (yokesIn>=0 && yokesIn<=5 && totalYokes+yokesIn<=5)
            {
                totalYokes=totalYokes+yokesIn;
                numOxen=numOxen+2*yokesIn;
                billSoFar=store.Buy(Oxen,yokesIn,money,priceIncreaseIn)+billSoFar;
                cout << "Current bill: $" << billSoFar << endl;break;
            }
            
            case 2: cout <<"How many pounds would you like to buy? Current food: " << poundsFood << endl;
            cin >> foodIn;
            while(foodIn*(0.5+(0.5*priceIncreaseIn))>money|| billSoFar>money|| foodIn+poundsFood>1000)
            {    
                if (foodIn*(0.5+(0.5*priceIncreaseIn))>money|| billSoFar>money)    
                {
                    cout << "You do not have sufficient money" << endl;                 //food
                    cin >>foodIn;
                }       
                else if (foodIn+poundsFood>1000)
                {
                    cout << "Cannot carry more than 1000 pounds of food. Try again. Current food: " << poundsFood<< endl;
                    cin >> foodIn;
                }
            }
            poundsFood=poundsFood+foodIn;
            billSoFar=store.Buy(Food,foodIn,money,priceIncreaseIn)+billSoFar;
            cout << "Current bill: $" << billSoFar << endl;break;

            case 3: cout << "How many boxes would you like to purchase? Current ammo: " << ammunition << endl;
            cin >> ammoIn;
            while (ammoIn*(2+(2*priceIncreaseIn))>money||billSoFar>money)             //ammo
            {                   
                cout << "You do not have sufficent money" << endl;
                cin >>ammoIn;
            }
            ammunition=ammoIn*20+ammunition;
            billSoFar=store.Buy(Bullets,ammoIn,money,priceIncreaseIn)+billSoFar;
            cout << "Current bill: $" << billSoFar <<endl;break;

            case 4: cout << "How many wagon parts would you like to purchase?" << endl;
            cin >>partsIn;
            while (partsIn*(20+(20*priceIncreaseIn))>money || billSoFar >money)
            {
                cout << "You do not have sufficient money" << endl;
                cin >> partsIn;
            }
            wagonParts=wagonParts+partsIn;
            billSoFar=store.Buy(Wagon,partsIn,money,priceIncreaseIn)+billSoFar;               //misc
            cout <<"How many medical kits would you like to purchase?" << endl;
            cin >> medicalIn;
            while(medicalIn*(25+(25*priceIncreaseIn))>money || billSoFar >money)
            {
                cout << "You do not have sufficient money" << endl;
                cin >>medicalIn; 
            }
            medicalSup=medicalIn+medicalSup;
            billSoFar=store.Buy(Medical,medicalIn,money,priceIncreaseIn)+billSoFar;
            cout << "Current bill: $" << billSoFar << endl;break;
            
            default: cout << "Please enter a valid input" << endl;break;
        }
        cout << "What would you like to purchase: (Numeric value)" << endl;
        cout << "1.Oxen\n2.Food\n3.Bullets\n4.Miscellaneous Supplies\n5.Exit store" << endl;
        cin >>buyingInput;
    }
    if (buyingInput==5)
    {
        while (totalYokes>5)
        {
            if (totalYokes>5)
            {
                cout << "Too many oxen yokes, please enter a number of yokes to reach 5 or less." << endl;
                cout << "Total yokes: " << totalYokes << endl;
                cin >> yokesIn;
                while (yokesIn*(40+(40*priceIncreaseIn))>money || billSoFar>money || yokesIn>5 || totalYokes+yokesIn>5)            //oxen
                {
                    if (yokesIn*(40+(40*priceIncreaseIn))>money || billSoFar>money)
                    {
                        cout << "You do not have sufficient money" << endl;
                        cin >> yokesIn;
                    }
                    else if (yokesIn>5 || totalYokes+yokesIn>5)
                    {
                        cout << "Cannot exceed 5 yokes of oxen." << endl;
                        cin >> yokesIn;
                    }
                }
                
                if (yokesIn>=0 && yokesIn<=5 && totalYokes<=5)
                {
                    totalYokes=totalYokes+yokesIn;
                    billSoFar=store.Buy(Oxen,yokesIn,money,priceIncreaseIn)+billSoFar;
                    cout << "Current bill: $" << billSoFar << endl;
                }
                cout<<"Total yokes: "<<totalYokes<<endl;
            }
        }
        money=money-billSoFar;
    }
}
void Game::startingStoreBuy()
{
    int yokesIn=0,foodIn=0,ammoIn=0,partsIn=0,medicalIn=0;
    double billSoFar=0,priceIncrease=0;
    int buyingInput;
    string date,Oxen="Oxen",Bullets="Bullets",Wagon="Wagon",Medical="Medical",Food="Food";
    Store startingStore=Store("startingStore", priceIncrease);                           //starting store

    cout << "==============================\nWelcome to the Starting Store\n==============================" << endl;
    cout << "YOU HAD SAVED $1600 TO SPEND FOR THE TRIP, AND YOU HAVE A WAGON. YOU WILL\nNEED TO SPEND THE REST OF YOUR MONEY ON THE FOLLOWING ITEMS:\n\n-  OXEN. YOU CAN SPEND $100-$200 ON YOUR TEAM. THE MORE YOU SPEND, THE FASTER\nYOU'LL GO BECAUSE YOU'LL HAVE BETTER ANIMALS.\n\n-  FOOD. THE MORE YOU HAVE, THE LESS CHANCE THERE IS OF GETTING SICK .\n\n-  AMMUNITION. YOU WILL NEED BULLETS FOR ATTACKS BY ANIMALS AND BANDITS, AND FOR HUNTING FOOD.\n\n-  MISCELLANEOUS SUPPLIES. THIS INCLUDES MEDICINE AND OTHER THINGS YOU WILL NEED FOR\nSICKNESS AND EMERGENCY REPAIRS.\n\nYOU CAN SPEND ALL YOUR MONEY BEFORE YOU START YOUR TRIP, OR YOU CAN SAVE SOME OF YOUR CASH\nTO SPEND AT FORTS ALONG THE WAY WHEN YOU RUN LOW. HOWEVER, ITEMS COST MORE AT THE FORTS.\nYOU CAN ALSO GO HUNTING ALONG THE WAY TO GET MORE FOOD." << endl;
    cout << endl;

    cout << "What would you like to purchase: (Numeric value)" << endl;
    cout << "1.Oxen\n2.Food\n3.Bullets\n4.Miscellaneous Supplies\n5.Exit store" << endl;
    cin >> buyingInput;
    while (buyingInput!=5)
    {
        switch (buyingInput)
        {                           //buying process
            case 1: cout << "There are 2 oxen in each yoke. Each yoke costs $40 and you must spend between $100-$200\nMust purchase between 3 and 5 yokes of oxen." << endl;
            cout << "How many yokes would you like to purchase?" << endl;
            cout << "Total yokes so far: " << totalYokes << endl;
            cin >> yokesIn;
            while (yokesIn*(40+(40*priceIncrease))>money || billSoFar>money || yokesIn>5 || totalYokes+yokesIn>5)            //oxen
            {
                if (yokesIn*(40+(40*priceIncrease))>money || billSoFar>money)
                {
                    cout << "You do not have sufficient money" << endl;
                    cin >> yokesIn;
                }
                else if (yokesIn>5 || totalYokes+yokesIn>5)
                {
                    cout << "Cannot exceed 5 yokes of oxen." << endl;
                    cin >> yokesIn;
                }
            }
            if (yokesIn>=0 && yokesIn<=5 && totalYokes+yokesIn<=5)
            {
                totalYokes=totalYokes+yokesIn;
                numOxen=yokesIn*2+numOxen;
                billSoFar=startingStore.Buy(Oxen,yokesIn,money,priceIncrease)+billSoFar;
                cout << "Current bill: $" << billSoFar << endl;break;
            }

            case 2: cout << "I recommend you purchase at least 200 pounds of food per person, at 50 cents per pound.\nHow many pounds would you like to buy?"<< endl;
            cin >> foodIn;
            while(foodIn*(0.5+(0.5*priceIncrease))>money|| billSoFar>money || foodIn>1000)
            {               
                if (foodIn*(0.5+(0.5*priceIncrease))>money|| billSoFar>money)
                {
                    cout << "You do not have sufficient money" << endl;                 //food
                    cin >>foodIn;
                }
                else if (foodIn>1000)
                {
                    cout << "Cannot carry more than 1000 pounds of food. Try again." << endl;
                    cin >>foodIn; 
                }
            }
            poundsFood=foodIn+poundsFood;
            billSoFar=startingStore.Buy(Food,foodIn,money,priceIncrease)+billSoFar;
            cout << "Current bill: $" << billSoFar << endl;break;

            case 3: cout << "A box of 20 bullets costs $2. You will need bullets for hunting along the way.\nHow many boxes would you like to purchase?" << endl;
            cin >> ammoIn;
            while (ammoIn*(2+(2*priceIncrease))>money||billSoFar>money)             //ammo
            {                   
                cout << "You do not have sufficent money" << endl;
                cin >>ammoIn;
            }
            ammunition=ammoIn*20+ammunition;
            billSoFar=startingStore.Buy(Bullets,ammoIn,money,priceIncrease)+billSoFar;
            cout << "Current bill: $" << billSoFar <<endl;break;

            case 4: cout << "All wagon parts costs $20 each and any part can be used to fix the wagon. Medical aid kits cost $25 each.\nHow many wagon parts would you like to purchase?" << endl;
            cin >>partsIn;
            while (partsIn*(20+(20*priceIncrease))>money || billSoFar >money)
            {
                cout << "You do not have sufficient money" << endl;
                cin >> partsIn;
            }
            wagonParts=partsIn+wagonParts;
            billSoFar=startingStore.Buy(Wagon,partsIn,money,priceIncrease)+billSoFar;               //misc
            cout <<"How many medical kits would you like to purchase?" << endl;
            cin >> medicalIn;
            while(medicalIn*(25+(25*priceIncrease))>money || billSoFar >money)
            {
                cout << "You do not have sufficient money" << endl;
                cin >>medicalIn; 
            }
            medicalSup=medicalIn+medicalSup;
            billSoFar=startingStore.Buy(Medical,medicalIn,money,priceIncrease)+billSoFar;
            cout << "Current bill: $" << billSoFar << endl;break;
            
            default: cout << "Please enter a valid input" << endl;break;
        }
        cout << "What would you like to purchase: (Numeric value)" << endl;
        cout << "1.Oxen\n2.Food\n3.Bullets\n4.Miscellaneous Supplies\n5.Exit store" << endl;
        cin >>buyingInput;
    }
    if (buyingInput==5)
    {
        while (totalYokes<3 || totalYokes>5)
        {
            if (totalYokes<3 || totalYokes>5)
            {
                cout << "Too many or too few oxen yokes, please enter a number of yokes to reach 3-5." << endl;
                cout << "Total yokes: " << totalYokes << endl;
                cin >> yokesIn;
                while (yokesIn*(40+(40*priceIncrease))>money || billSoFar>money || yokesIn>5 || totalYokes+yokesIn>5)            //oxen
                {
                    if (yokesIn*(40+(40*priceIncrease))>money || billSoFar>money)
                    {
                        cout << "You do not have sufficient money" << endl;
                        cin >> yokesIn;
                    }
                    else if (yokesIn>5 || totalYokes+yokesIn>5)
                    {
                        cout << "Cannot exceed 5 yokes of oxen." << endl;
                        cin >> yokesIn;
                    }
                }
                
                if (yokesIn>=0 && yokesIn<=5 && totalYokes<=5)
                {
                    totalYokes=totalYokes+yokesIn;
                    billSoFar=startingStore.Buy(Oxen,yokesIn,money,priceIncrease)+billSoFar;
                    cout << "Current bill: $" << billSoFar << endl;
                }
                cout<<"Total yokes: "<<totalYokes<<endl;
            }
        }
        money=money-billSoFar;
        numOxen=totalYokes*2;
    }
}
void Game::setAlivePlayer(int playerAlivein)
{
    numPlayersAlive=playerAlivein;
}
int Game::getAlivePlayers()
{
    return numPlayersAlive;
}
double Game::getMoney()
{
    if (money>=0)
    {
        return money;
    }
    else
    {
        money=0;
        return money;
    }
   
}
void Game::setMoney(double moneyIn)
{
    money=moneyIn;
}
int Game::getMilage()
{
    return milage;
}
void Game::setMilage(int milesIn)
{
    milage=milesIn;
}
int Game::getFood()
{
    if (poundsFood>=0)
    {
        return poundsFood;
    }
    else
    {
        poundsFood=0;
        return poundsFood;
    }
    
}
void Game::setFood(int foodIn)
{
    poundsFood=foodIn;
}
int Game::getAmmo()
{
    return ammunition;
}
void Game::setAmmo(int ammoIn)
{
    ammunition=ammoIn;
}
int Game::getOxen()
{
    return numOxen;
}
void Game::setOxen(int oxenIn)
{
    numOxen=oxenIn;
}
int Game::getMedical()
{
    return medicalSup;
}
void Game::setMedical(int medicalIn)
{
    medicalSup=medicalIn;
}
int Game::getWagon()
{
    return wagonParts;
}
void Game::setWagon(int wagonIn)
{
    wagonParts=wagonIn;
}
string Game::getNamePlayers()
{
    for (int i=0;i<5;i++)
    {
        return players[i].getPlayerName();
    }
    return 0;
}
bool Game::isGameOver()
{
    return gameOverBool;
}
void Game::setGameOver(bool gameoverIn)
{
    gameOverBool=gameoverIn;
}
void Game::getDate()
{
    switch (date.getMonth())
    {
        case 3: cout << "March " << date.getDay() << endl;break;
        case 4: cout << "April " << date.getDay() << endl;break;
        case 5: cout << "May " << date.getDay() << endl;break;
        case 6: cout << "June " << date.getDay() << endl;break;
        case 7: cout << "July " << date.getDay() << endl;break;
        case 8: cout << "August " << date.getDay() << endl;break;
        case 9: cout << "September " << date.getDay() << endl;break;
        case 10: cout << "October " << date.getDay() << endl;break;
        case 11: cout << "November " << date.getDay() << endl;break;
    }
}
Milestone Game::nextMile(int milestonePos)
{
    return milestones[milestonePos];
}
void Game::hunt()
{
    srand(time(0));
    int probabilityAnimal,puzzleValue,playerPuzzleINPUT,eatInput,huntInput;
    int day=date.getDay();
    int month=date.getMonth();
    cout << "Hunting takes 1 day. You can encounter rabbits, foxes, deer, bear, or moose.\nProbability are as followed:\nRabbit: 50%\nFox: 25%\nDeer: 15%\nBear: 7%\nMoose: 5%" << endl;
    daysPast=1;
    day=day+daysPast;
    updateDayMonth(daysPast);                    //Hunt
    probabilityAnimal=rand()%((100-1)+1)+1;
    if (probabilityAnimal>0 && probabilityAnimal<51)                //rabbit
    {
        cout << "You got lucky! You encountered a rabbit! Do you want to hunt? (Numeric Value)\n1. Yes\n2. No" << endl;
        cin >> huntInput;
        while (huntInput != 1 && huntInput != 2)
        {
            cout << "Invalid option please try again." << endl;
            cin >> huntInput;
        }
        switch (huntInput)
        {
            case 1: if (ammunition<10)                   //rabbit choose to hunt
            {
                cout << "Hunt unsuccessful :( not enough ammunition." << endl;break;
            }
            else
            {
                puzzleValue=rand()%((5-1)+1)+1;
                cout << "We have chosen a number between 1 and 5. If you guess the number correctly\nthe hunt will be successful (3 tries). If not then the hunt will be unsuccessful." << endl;
                for (int i=0;i<3;i++)
                {
                    cin >> playerPuzzleINPUT;
                    if (playerPuzzleINPUT==puzzleValue)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Try again" << endl;
                    }
                }
                if (playerPuzzleINPUT==puzzleValue)
                {
                    poundsFood=poundsFood+5;
                    ammunition=ammunition-10;
                    cout << "Hunt successful!" << endl;break;
                }
                else
                {
                    cout << "Hunt unsuccessful :(" << endl;break;
                }
            }
            case 2: cout << "Not feeling rabbit? No problem!" << endl;break;                                             //choose not to hunt
        }
    }
    if (probabilityAnimal>0 && probabilityAnimal<26)
    {
        cout << "You got lucky! You encountered a fox! Do you want to hunt? (Numeric Value)\n1. Yes\n2. No" << endl;
        cin >> huntInput;
        while (huntInput != 1 &&huntInput != 2)
        {
            cout << "Invalid option please try again." << endl;
            cin >> huntInput;
        }
        switch (huntInput)
        {
            case 1: if (ammunition<8)                   //fox choose to hunt
            {
                cout << "Unsuccessful hunt :( not enough ammunition" << endl;break;
            }
            else
            {
                puzzleValue=rand()%((5-1)+1)+1;
                cout << "We have chosen a number between 1 and 5. If you guess the number correctly\nthe hunt will be successful (3 tries). If not then the hunt will be unsuccessful." << endl;
                for (int i=0;i<3;i++)
                {
                    cin >> playerPuzzleINPUT;
                    if (playerPuzzleINPUT==puzzleValue)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Try again" << endl;
                    }
                }
                if (playerPuzzleINPUT==puzzleValue)
                {
                    poundsFood=poundsFood+10;
                    ammunition=ammunition-8;
                    cout << "Hunt successful!" << endl;break;
                }
                else
                {
                    cout << "Unsuccessful hunt :(" << endl;break;
                }
            }
            case 2: cout << "Not feeling fox? No problem!" << endl;break;                                             //choose not to hunt
        }
    }
    if (probabilityAnimal>0 && probabilityAnimal<16)
    {
        cout << "You got lucky! You encountered a deer! Do you want to hunt? (Numeric Value)\n1. Yes\n2. No" << endl;
        cin >> huntInput;
        while (huntInput != 1 &&huntInput != 2)
        {
            cout << "Invalid option please try again." << endl;
            cin >> huntInput;
        }
        switch (huntInput)
        {
            case 1: if (ammunition<10)                   //deer choose to hunt
            {
                cout << "Unsuccessful hunt :(" << endl;break;
            }
            else
            {
                puzzleValue=rand()%((5-1)+1)+1;
                cout << "We have chosen a number between 1 and 5. If you guess the number correctly\nthe hunt will be successful (3 tries). If not then the hunt will be unsuccessful." << endl;
                for (int i=0;i<3;i++)
                {
                    cin >> playerPuzzleINPUT;
                    if (playerPuzzleINPUT==puzzleValue)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Try again" << endl;
                    }
                }
                if (playerPuzzleINPUT==puzzleValue)
                {
                    poundsFood=poundsFood+60;
                    ammunition=ammunition-5;
                    cout << "Hunt successful!" << endl;break;
                }
                else
                {
                    cout << "Unsuccessful hunt :(" << endl;break;
                }
            }
            case 2: cout << "Not feeling deer? No problem!" << endl;break;                                              //choose not to hunt
        }
    }
    if (probabilityAnimal>0 && probabilityAnimal<8)
    {
        cout << "You got lucky! You encountered a bear! Do you want to hunt? (Numeric Value)\n1. Yes\n2. No" << endl;
        cin >> huntInput;
        while (huntInput != 1 && huntInput != 2)
        {
            cout << "Invalid option please try again." << endl;
            cin >> huntInput;
        }
        switch (huntInput)
        {
            case 1: if (ammunition<10)                   //bear choose to hunt
            {
                cout << "Unsuccessful hunt :(" << endl;break;
            }
            else
            {
                puzzleValue=rand()%((5-1)+1)+1;
                cout << "We have chosen a number between 1 and 5. If you guess the number correctly\nthe hunt will be successful (3 tries). If not then the hunt will be unsuccessful." << endl;
                for (int i=0;i<3;i++)
                {
                    cin >> playerPuzzleINPUT;
                    if (playerPuzzleINPUT==puzzleValue)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Try again" << endl;
                    }
                }
                if (playerPuzzleINPUT==puzzleValue)
                {
                    poundsFood=poundsFood+200;
                    ammunition=ammunition-10;
                    cout << "Hunt successful!" << endl;break;
                }
                else
                {
                    cout << "Unsuccessful hunt :(" << endl;break;
                }
                
            }
            case 2: cout << "Not feeling bear? No problem!" << endl;break;                                              //choose not to hunt
        }
    }
    if (probabilityAnimal>0 && probabilityAnimal<6)
    {
        cout << "You got lucky! You encountered a moose! Do you want to hunt? (Numeric Value)\n1. Yes\n2. No" << endl;
        cin >> huntInput;
        while (huntInput != 1&&huntInput != 2)
        {
            cout << "Invalid option please try again." << endl;
            cin >> huntInput;
        }
        switch (huntInput)
        {
            case 1: if (ammunition<12)                   //moose choose to hunt
            {
                cout << "Unsuccessful hunt :(" << endl;break;
            }
            else
            {
                puzzleValue=rand()%((5-1)+1)+1;
                cout << "We have chosen a number between 1 and 5. If you guess the number correctly\nthe hunt will be successful (3 tries). If not then the hunt will be unsuccessful." << endl;
                for (int i=0;i<3;i++)
                {
                    cin >> playerPuzzleINPUT;
                    if (playerPuzzleINPUT==puzzleValue)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Try again" << endl;
                    }
                }
                if (playerPuzzleINPUT==puzzleValue)
                {
                    poundsFood=poundsFood+500;
                    ammunition=ammunition-12;
                    cout << "Hunt successful!" << endl;break;
                }
                else
                {
                    cout << "Unsuccessful hunt :(" << endl;break;
                }
            }
            case 2: cout << "Not feeling moose? No problem!" << endl;break;                                             //choose not to hunt
        }
    }
    cout << "How well would you like to eat?\n1. Poorly (2 pounds per person)\n2. Moderatly (3 pounds per person)\n3. Well (5 pounds per person)" << endl;
    cin >> eatInput;
    while (eatInput!= 1 && eatInput!= 2 && eatInput!=3)
    {
        cout << "Invalid option please try again." << endl;
        cin >> eatInput;
    }
    switch (eatInput)
    {
        case 1: poundsFood=poundsFood-(2*numPlayersAlive);break;          //Poor
        case 2: poundsFood=poundsFood-(3*numPlayersAlive);break;      //Mod
        case 3: poundsFood=poundsFood-(5*numPlayersAlive);break;         //Well
    }
    if (poundsFood>1000)
    {                                                                                       //hunt
        cout << "The wagon can only hold 1000 lbs of food. Some had to be dropped." << endl;
        poundsFood=1000;
    }
}
void Game::updateDayMonth(int daysPastIn)
{
    int day,month;
    day=date.getDay();
    month=date.getMonth();
    daysPast=daysPastIn;
    day=day+daysPast;
    if (month==3 && day>31)
    {
        month=4;
        day=day-31;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month==4 && day > 30)
    {
        month = 5;
        day=day-30;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month ==5 && day > 31)
    {
        month =6;
        day=day-31;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month==6 && day > 30)
    {
        month=7;
        day=day-30;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month==7 && day >31)
    {
        month =8;
        day=day-31;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month==8 && day >31)
    {
        month =9;
        day=day-31;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month ==9 && day >30)
    {
        month =10;
        day=day-30;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month ==10 && day >31)
    {
        month =11;
        day=day-31;
        date.setDay(day);
        date.setMonth(month);
    }
    else if (month==11 && day >30)
    {
        cout << "You couldn't make it before winter! Try again!" << endl;
        gameOverBool=true;
    }
    else
    {
        date.setDay(day);
        date.setMonth(month);
    }
    
}
int Game::continueTrip(int milestonePos)
{
    int milesTrav;
    cout << "Continuing takes 2 weeks. The party will consume 3 pounds of food, per person, per day.\nYou will typically travel between 70 and 140 miles." << endl;
    daysPast=14;
    updateDayMonth(daysPast);
    poundsFood=poundsFood-(3*daysPast*numPlayersAlive);                               //Continue
    milesTrav=rand()%((140-70)+1)+70;
    if (milesTrav>nextMile(milestonePos).getmilestoneMilage()-milage)
    {
        milage=nextMile(milestonePos).getmilestoneMilage();
        milestonePos++;
    }
    else
    {
        milage=milage+milesTrav;
    }
    return milestonePos;
}
void Game::rest()
{
    cout << "Resting takes between 1 and 3 days. The party will consume 3 pounds of food, per person, per day." << endl;
    daysPast=(rand()%3)+1;                                              //Rest
    updateDayMonth(daysPast);
    poundsFood=poundsFood-(3*daysPast*numPlayersAlive);
}
void Game::raiderAttack()
{
    srand(time(0));
    int raiderInput, puzzleValue, puzzleInput, randoNumber=rand()%((100-1)+1)+1;
    double probRaider,top,bottom;

    top=((pow((double(milage)/(100.0-4.0)),2.0))+72.0);
    bottom=((pow((double(milage)/(100.0-4.0)),2.0))+12.0);
    probRaider=((top/bottom)-1)/0.1;
    probRaider=round(probRaider);

    if (randoNumber<= probRaider && randoNumber >= 0 )
    {
        cout << "\nRIDERS AHEAD! THEY LOOK HOSTILE!\n" << endl;
        cout << "Would you like to:\n1. Run\n2. Attack\n3. Surrender" << endl;
        cin >> raiderInput;
        while (raiderInput!= 1 && raiderInput!=2 && raiderInput!=3)
        {
            cout << "Invalid option, try again." << endl;
            cin >> raiderInput;
        }
        switch (raiderInput)
        {
            case 1: cout << "The travelling party escapes with their lives but, in the hurry to flee the raiders\nyou've left behind 1 ox, 10 lbs. of food, and 1 wagon part." <<endl;
            numOxen--;
            if (numOxen%2==0)
            {
                totalYokes--;;                                      //Run
            }
            poundsFood=poundsFood-10;
            wagonParts--;
            cout << "Your remaining oxen are: " << numOxen << "\nYour remaining pounds of food are: " << poundsFood << "\nYour remaining wagon parts are: " << wagonParts << endl;break;

            case 2: puzzleValue=rand()%((10-1)+1)+1;
            cout << "We have chosen a number between 1 and 10. If you guess the number correctly\nthe attack will be successful (3 tries). If not then the attack will be unsuccessful." << endl;
            for (int i=0;i<3;i++)
            {
                cin >> puzzleInput;
                if (puzzleInput==puzzleValue)
                {
                    break;
                }
                else
                {
                    cout << "Try again" << endl;
                }
            }
            if (puzzleInput==puzzleValue)
            {
                poundsFood=poundsFood+50;
                ammunition=ammunition+50;
                cout << "Attack successful! You've gained 50 pounds of food and 50 bullets." << endl;break;
            }
            else
            {
                ammunition=ammunition-50;
                money=money-(money/4);
                cout << "Attack unsuccessful! You've lost 50 bullets and a quarter of your cash reserves."<< endl;
            }
            break;

            case 3: cout << "You've lost a quarter of your cash reserves." << endl;
            money=money-(money/4.0);
            break;
        }
    }
}
void Game::misfortune()
{
    srand(time(0));
    string sickness;
    int sicknessValue,sickPerson,ChoosingDeath,isPersonDead;
    int day=date.getDay();
    int month=date.getMonth();
    int misfortuneProb=rand()%((100-1)+1)+1;
    if (misfortuneProb>0 && misfortuneProb <41)
    {
        int misfortuneValue=rand()%((3-1)+1)+1;
        switch (misfortuneValue)
        {
            case 1: 
            sickPerson=rand()%(5-0);                  
            while (players[sickPerson].getIsDead()==true)//sick member
            {
                sickPerson=rand()%(5-0);
            }
            sicknessValue=rand()%((6-1)+1)+1;
            switch(sicknessValue)
            {
                case 1: sickness="Typhoid";
                cout << "\n===Oh no! " << players[sickPerson].getPlayerName() << " has " << sickness << "!===\n" << endl;break;
                case 2: sickness="Cholera";
                cout << "\n===Oh no! " << players[sickPerson].getPlayerName() << " has " << sickness << "!===\n" << endl;break;
                case 3: sickness= "Diarrhea";
                cout << "\n===Oh no! " << players[sickPerson].getPlayerName() << " has " << sickness << "!===\n" << endl;break;
                case 4: sickness="Measles";
                cout << "\n===Oh no! " << players[sickPerson].getPlayerName() << " has " << sickness << "!===\n" << endl;break;
                case 5: sickness="Dysentery";
                cout << "\n===Oh no! " << players[sickPerson].getPlayerName() << " has " << sickness << "!===\n" << endl;break;
                case 6: sickness="Fever";
                cout << "\n===Oh no! " << players[sickPerson].getPlayerName() << " has a " << sickness << "!===\n" << endl;break;
            }
            if (medicalSup>0)
            {
                cout << "You have a medical kit! It's been used to heal " << players[sickPerson].getPlayerName() << ". They still have 50% chance to die." << endl;
                medicalSup--;
                isPersonDead=rand()%((100-1)+1)+1;
                if (isPersonDead>0 && isPersonDead <51)
                {
                    cout << "------Oh no! " << players[sickPerson].getPlayerName() << " died!------" << endl;
                    players[sickPerson].setIsDead(true);
                    numPlayersAlive--;
                }
                else
                {
                    cout << "-----" << players[sickPerson].getPlayerName() << " healed!-----" << endl;
                }
                cout << "You still have " << medicalSup << " medical kits remaining."  <<endl;break;
            }      
            else
            {
                cout << "You dont have any med kits. Would you like to rest or press on!\n1. Rest: party must rest for 3 days but sick player has 30% chance to die.\n2. Press On!: party will continue but sick player has 70% chance to die." << endl;
                cin >> ChoosingDeath;
                while (ChoosingDeath!= 1 && ChoosingDeath!=2)
                {
                    cout << "Invalid option, try again." << endl;
                    cin >> ChoosingDeath;
                }
                switch (ChoosingDeath)
                {
                    case 1: 
                    daysPast=3;
                    isPersonDead=rand()% ((100-1)+1)+1;
                    if (isPersonDead>0 && isPersonDead <31)
                    {
                        cout << players[sickPerson].getPlayerName() << " died!" << endl;
                        numPlayersAlive--;
                        players[sickPerson].setIsDead(true);break;
                    }
                    case 2: isPersonDead=rand()% ((100-1)+1)+1;
                    if (isPersonDead>0 && isPersonDead <71)
                    {
                        cout << players[sickPerson].getPlayerName() << " died!" << endl;
                        numPlayersAlive--;
                        players[sickPerson].setIsDead(true);break;                                         //Press On
                    }
                }  
            } 
            break;    

            case 2:                                                           //oxen dies
            numOxen--;;;
            if (numOxen%2==0)
            {
                totalYokes--;;
            }
            cout << "Oh no! One of your oxen has died! You have " << numOxen << " left!" << endl;break;

            case 3:                                              //part breaks
            cout << "Oh no! A wagon part has broken!" << endl;
            if (wagonParts>0)
            {
                cout << "A wagon part was used to fix it!" << endl;
                wagonParts--;
                cout << "Remaining parts: " << wagonParts <<endl;
                break;
            }
            else
            {
                gameOverBool=true;break;
            }                                                        
        }
    }
}
void Game::gameOver()
{
    ofstream file;
    string line;
    file.open("results.txt",ios_base::app);
    cout << "Game over! We're sorry you couldn't make it to Oregon City." << endl;
    cout << "Player: " << players[0].getPlayerName() << ", miles traveled: " << milage << ", food remaining: " << poundsFood << ", cash remaining: " << money << endl;
    file << "Player: " << players[0].getPlayerName() << ", miles traveled: " << milage << ", food remaining: " << poundsFood << ", cash remaining: " << money << endl;
    file.close();
}
void Game::statusUpdate(int playerTurn,int milestonePos)
{
    cout << "\n====================\nSTATUS UPDATE\n-Current date: ";
    getDate();
    cout << "-Miles traveled: " << milage<<"\n-Next milestone: "<<nextMile(milestonePos).getMilestoneName() << " " << nextMile(milestonePos).getmilestoneMilage()-milage << " miles away.\n-Food available: " << poundsFood<<"\n-Number of bullets available: " << ammunition << "\n-Cash available: $" << money << "\n===================="<< endl;
    cout << "\nPlayer: " << players[playerTurn].getPlayerName() << " it's your turn!" << endl;
}
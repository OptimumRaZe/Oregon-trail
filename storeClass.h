#ifndef STORECLASS_H
#define STORECLASS_H
#include <string>

using namespace std;

class Store
{
    public:
    Store();
    Store(string storeName,double priceIncreaseIn);
    double getPriceIncrease();
    void setPriceIncrease(double priceIncreaseIn);
    double Buy(string itemName,int quantity, double money, double priceIncrease);
    double getTotalPrice();
    string getStoreName();
    void setStoreName(string nameIn);

    private:
    double priceIncrease;
    double totalPrice;
    int oxenBought;
    int foodBought;
    int bulletsBought;
    int wagonBought;
    int medicalBought;
    string storeName;
};

#endif
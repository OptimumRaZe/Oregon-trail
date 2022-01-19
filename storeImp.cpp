#include <iostream>
#include <string>
#include "storeClass.h"

Store::Store()
{
    priceIncrease=0;
    storeName="";
}
Store::Store(string storeNameIn,double priceIncreaseIn)
{
    priceIncrease=priceIncreaseIn;
    storeName=storeNameIn;
}
double Store::getPriceIncrease()
{
    return priceIncrease;
}
void Store::setPriceIncrease(double priceIncreaseIn)
{
    priceIncrease=priceIncreaseIn;
}
double Store::getTotalPrice()
{
    return totalPrice;
}
double Store::Buy(string itemName, int quantity, double money, double priceIncrease)
{
    totalPrice=0;
    if (itemName=="Oxen")
    {
        oxenBought=quantity;
        totalPrice=(40+(40*priceIncrease))*oxenBought;
    }
    if (itemName=="Food")
    {
        foodBought=quantity;
        totalPrice=(0.5+(0.5*priceIncrease))*foodBought;
    }
    if (itemName=="Bullets")
    {
        bulletsBought=quantity;
        totalPrice=(2+(2*priceIncrease))*bulletsBought;
    }
    if (itemName=="Wagon")
    {
        wagonBought=quantity;
        totalPrice=(20+(20*priceIncrease))*wagonBought;
    }
    if (itemName=="Medical")
    {
        medicalBought=quantity;
        totalPrice=(25+(25*priceIncrease))*medicalBought;
    }
    return totalPrice;
}
string Store::getStoreName()
{
    return storeName;
}
void Store::setStoreName(string nameIn)
{
    storeName=nameIn;
}
#include <iostream>
#include <string>
#include "dateClass.H"
Date::Date()
{
    month=0;
    day=0;
}
Date::Date(int monthIn, int dayIn)
{
    month=monthIn;
    day=dayIn;
}
int Date::getMonth()
{
    return month;
}
int Date::getDay()
{
    return day;
}
void Date::setDay(int dayIn)
{
    day=dayIn;
}
void Date::setMonth(int monthIn)
{
    month=monthIn;
}
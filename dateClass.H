#ifndef DATECLASS_H
#define DATECLASS_H
#include <string>

using namespace std;

class Date
{
    public:
    Date();
    Date(int monthIn,int dayIn);
    int getMonth();
    void setMonth(int monthIn);
    int getDay();
    void setDay(int dayIn);

    private:
    int day;
    int month;
};
#endif
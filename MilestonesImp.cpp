#include <iostream>
#include <string>
#include "milestonesClass.h"

Milestone::Milestone()
{
    milestoneName="";
    milestoneMilage=0;
    isFort=false;
}
Milestone::Milestone(string milestoneIn, int milestoneMilageIn, bool isFortIn)
{
    milestoneName=milestoneIn;
    milestoneMilage=milestoneMilageIn;
    isFort=isFortIn;
}
string Milestone::getMilestoneName()
{
    return milestoneName;
}
void Milestone::setMilestoneName(string milestoneNameIn)
{
    milestoneName=milestoneNameIn;
}
int Milestone::getmilestoneMilage()
{
    return milestoneMilage;
}
void Milestone::setMilestoneMilage(int milestoneMilageIn)
{
    milestoneMilage=milestoneMilageIn;
}
bool Milestone::getisFort()
{
    return isFort;
}
void Milestone::setisFort(bool isFortIn)
{
    isFort=isFortIn;
}
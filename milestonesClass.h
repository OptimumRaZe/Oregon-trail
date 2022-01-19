#ifndef MILESTONESCLASS_H
#define MILESTONESCLASS_H
#include <string>

using namespace std;

class Milestone
{
    public:
    Milestone();
    Milestone(string milestoneIn, int milestoneMilageIn, bool isFortIn);
    string getMilestoneName();
    void setMilestoneName(string milestoneNameIn);
    int getmilestoneMilage();
    void setMilestoneMilage(int milestoneMilageIn);
    bool getisFort();
    void setisFort(bool isFortIn);

    private:
    string milestoneName;
    int milestoneMilage;
    bool isFort;
};

#endif
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/* Global variable */
/*
  * itemType = item_reward || item_due
  * scheduleType = scheduleIndex || itemIndex || item_reward
*/
typedef pair <int, int> iType;
typedef pair <int, pair< int, int > > sType;
typedef vector< iType > itemType;
typedef vector< sType > scheduleType;
itemType item;
int DUE=0, MACHINE=0;

void fileRead(void);  //read the input file
void fileOut(scheduleType& s1, scheduleType&s2); //write output file
void InitSchdule(scheduleType& src);//init schdule variable from src to null
void InitSchdule(scheduleType& src, scheduleType& dst);//init schdule variable from src to dst
void findThebest(scheduleType& schedule);//find the best reward
void findThesecond(scheduleType& schedule);//find the second best reward
bool push_rightDay(scheduleType& sch, itemType::iterator& it, int* index);//if the input item's due is equal the schedule due
void push_beforeDay(scheduleType& sch, itemType::iterator& it, int* index);//else if we choose the day before the due
int countThereward(scheduleType& schedule);//count the reward from the found case
void setNonBestItem(vector< int >& dst, scheduleType& sample);//find the item not included to the best or the second best
/* sorting function */
bool sortBy2(const sType&a, const sType&b) {return a.second.second < b.second.second;}
bool sortBy3(const sType&a, const sType&b) {return a.second.second > b.second.second;}
bool byDesc1(const iType& a, const iType& b){return a.first > b.first;}
void sortItembyDue(void);
int main(void)
{
    /* INPUT READ */
    fileRead();

    /* VAR DECLATION */
    scheduleType schedule_1st, schedule_2nd;

    /* FIND BEST & SECOND */
    InitSchdule(schedule_1st);
    findThebest(schedule_1st);

    InitSchdule(schedule_1st, schedule_2nd);
    findThesecond(schedule_2nd);

    /* OUTPUT WRITE */
    fileOut(schedule_1st, schedule_2nd);
    return 0;
}
void fileRead(void)
{
    int numOflist=0;

    ifstream ifs("machine.inp");
    if(!ifs.fail())
    {
        ifs >> numOflist >> DUE >> MACHINE;
        for(int i=0; i<numOflist; ++i)
        {
            int _reward=0, _due=0;
            ifs >> _reward >> _due;
            item.push_back(make_pair(_reward, _due));
        }
        ifs.close();
    } else {
        cout << "Failed to open Input file " << endl;
        return ;
    }
}
void fileOut(scheduleType&s1, scheduleType& s2)
{
    ofstream ofs("machine.out");
    ofs << countThereward(s1) << ' ' << countThereward(s2);
    ofs.close();
}
void InitSchdule(scheduleType& sch)
{
    for(int i=0; i<MACHINE*DUE; ++i)
        sch.push_back(make_pair(i, make_pair(-1, 0)));//Index, reward
}
void InitSchdule(scheduleType& src, scheduleType& dst)
{
    if(dst.size() != 0)
        dst.clear();
    for(scheduleType::iterator it=src.begin();
        it!=src.end(); ++it)
        {
            dst.push_back(make_pair((*it).first, make_pair((*it).second.first, (*it).second.second)));
        }
}
void findThebest(scheduleType& s1)
{
    /* sorting */
    sort(item.begin(), item.end(), byDesc1); //descending
    sortItembyDue();
    int index=0;
    /* BEST COST */
    for(itemType::iterator it=item.begin();
        it!=item.end(); ++it)
        {
              //Execute by MACHINE
              //cout << "("<< index+1 << ") item reward/due :" << (*it).first << '/' << (*it).second << endl;
              if(push_rightDay(s1, it, &index) == false)
              {
                  push_beforeDay(s1, it, &index);
              }
              //cout << endl;
              index++;
        }
    //cout << "Item currupted " << endl;
    //item=copyOfItem;
}
bool push_rightDay(scheduleType& sch, itemType::iterator& it, int* index)
{
    int item_due=(*it).second-1;
    for(int i=0; i<MACHINE; ++i)
    {
        int schIndex=i*DUE+item_due;
        if(sch[schIndex].second.second == 0)
        {
            sch[schIndex].first = schIndex;//schedule Index
            sch[schIndex].second.first = (*index);//Item Index
            sch[schIndex].second.second = (*it).first;//reward value
            return true;
        }
        else{;}
    }
    return false;
}
void push_beforeDay(scheduleType& sch, itemType::iterator& it, int* index)
{
    int item_due=(*it).second-1;
    for(int j=item_due; j>0; --j)
    {
        for(int i=0; i<MACHINE; ++i)
        {
            int schIndex2=i*DUE+(j-1);
            if(sch[schIndex2].second.second == 0)
            {
                sch[schIndex2].first = schIndex2;
                sch[schIndex2].second.first = (*index);
                sch[schIndex2].second.second = (*it).first;
                return;
            }
            else{;}
        }
    }
}
void findThesecond(scheduleType& secondBest)
{
    //Non-best time which means Excluding the best case.
    /* Redefine
      * the 1st is changed
      * itemType = item_index ||
    */
    //Init nonBestItem
    scheduleType sch=secondBest;
    vector< int > nonBestItem; //The items of excluding the best schedule.
    setNonBestItem(nonBestItem, sch);

    //Best_list sorting
    sort(sch.begin(), sch.end(), sortBy3);//ordery by reward

    /* Redefine
      * the 3rd is changed
      * scheduleType = schedule || item_index || the diff(=bestReward - secondReward)
    */
    scheduleType diff;
    //case1.substaction
    unsigned int subtract=sch.size()-1;
    for(; subtract>0 &&sch[subtract].second.second==0; --subtract);
    diff.push_back(make_pair(subtract, make_pair(-1, sch[subtract].second.second)));

    //case2.surplus index

    for(scheduleType::iterator it=sch.begin();
      it!=sch.end(); ++it)
      {
          int schIndex=(*it).first,
              bestReward=(*it).second.second;
          int target_due=schIndex%DUE+1;
          //In the nonBestItem
          for(vector< int >::iterator nit=nonBestItem.begin();
              nit!=nonBestItem.end(); ++nit)
              {
                  int i=(*nit);
                  int secondReward=item[i].first, secondDue=item[i].second;
                  if(target_due <= secondDue
                    &&bestReward!=secondReward) //Can be answer Answer
                  {
                      int _diff=bestReward - secondReward;
                      if(_diff > 0) diff.push_back(make_pair(schIndex, make_pair(i, _diff)));
                  }
              }
      }

    //sorting the diff
    sort(diff.begin(), diff.end(), sortBy2);

    //setting the schedule_2nd
    if(diff[0].second.first == -1) //case1 -> Delete
    {
        int sub_index=sch[subtract].first;
        secondBest[sub_index].first=sub_index;
        secondBest[sub_index].second.first=-1;
        secondBest[sub_index].second.second=0;
    } else // case2 -> Switching
    {
        int switchInd=diff[0].first, switchItem=diff[0].second.first;
        secondBest[switchInd].first=switchInd;
        secondBest[switchInd].second.first=switchItem;
        secondBest[switchInd].second.second=item[switchItem].first;
    }
}
int countThereward(scheduleType& sch)
{
    int sz=MACHINE*DUE, reward=0;;
    for(int i=0; i<sz; ++i)
        reward+=sch[i].second.second;
    return reward;
}
void setNonBestItem(vector< int >& dst, scheduleType& sample)
{
    //sample
    vector< int > src;//the best indexes
    for(scheduleType::iterator it=sample.begin();
        it!=sample.end(); ++it)
        {
            if((*it).second.first != -1)
            {
              src.push_back((*it).second.first);//push the 'item' indexes from 'bestSchedule'
            }
        }
    //set dst
    for(unsigned i=0; i<item.size(); ++i)
    {
        vector< int >::iterator _find=find(src.begin(), src.end(), i);
        if(_find == src.end())
        {
          dst.push_back(i);
        }
        else{;}
    }
}
void sortItembyDue(void)
{
    for(itemType::iterator src=item.begin();
          src!=item.end(); src++)
          {
              for(itemType::iterator dst=src+1;
                  dst!=item.end() && (*src).first == (*dst).first; ++dst)
                  {
                      if((*src).second > (*dst).second)
                      {
                          iType temp=(*src);
                          (*src)=(*dst);
                          (*dst)=temp;
                      }
                  }
          }
}

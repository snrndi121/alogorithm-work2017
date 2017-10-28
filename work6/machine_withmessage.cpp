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

void fileRead(void);
void InitSchdule(scheduleType& sch);
void InitSchdule(scheduleType& src, scheduleType& dst);
void findThebest(scheduleType& schedule);
void findThesecond(scheduleType& schedule);
bool push_rightDay(scheduleType& sch, itemType::iterator& it, int* index);
void push_beforeDay(scheduleType& sch, itemType::iterator& it, int* index);
int countThereward(scheduleType& schedule);
void setNonBestItem(vector< int >& dst, scheduleType& sample);
/* Optional sector */
bool sortBy2(const sType&a, const sType&b) {return a.second.second < b.second.second;}
bool sortBy3(const sType&a, const sType&b) {return a.second.second > b.second.second;}
bool byDesc1(const iType& a, const iType& b){return a.first > b.first;}
void dueSwitching(void)
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
void filePrint(itemType& _item)
{
    cout << "item_size : " << _item.size() << endl;
    for(itemType::iterator it=_item.begin();
        it!=_item.end(); ++it)
        {
            cout << (*it).first << ' ' << (*it).second << endl;
        }
    return ;
}
void schPrint(scheduleType& _sch)
{
    int i=0;
    for(scheduleType::iterator it=_sch.begin();
        it!=_sch.end(); ++it)
    {
        int item_index=(*it).second.first;
        if((i++)%DUE ==0){cout << endl;}
        cout << '(' << (*it).first << ')' << (*it).second.second << '/' << item[item_index].second << ' ';
    }
    cout << "\n\n";
}
int main(void)
{
    /* INPUT READ */
    fileRead();//filePrint();

    /* VAR DECLATION */
    scheduleType schedule_1st, schedule_2nd;
    InitSchdule(schedule_1st);
    findThebest(schedule_1st);

    InitSchdule(schedule_1st, schedule_2nd);
    findThesecond(schedule_2nd);
    schPrint(schedule_1st);
    cout << "Best reward :" << countThereward(schedule_1st) << endl;

    schPrint(schedule_2nd);
    cout << "Second reward :" << countThereward(schedule_2nd) << endl;
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
    //filePrint(item);
    sort(item.begin(), item.end(), byDesc1); //descending
    //filePrint(item);
    dueSwitching();
    filePrint(item);
    //itemType copyOfItem=item;
    int index=0;
    /* BEST COST */
    for(itemType::iterator it=item.begin();
        it!=item.end(); ++it)
        {
              //Execute by MACHINE
              cout << "("<< index+1 << ") item reward/due :" << (*it).first << '/' << (*it).second << endl;
              if(push_rightDay(s1, it, &index) == false)
              {
                  push_beforeDay(s1, it, &index);
              }
              cout << endl;
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
        cout << "info :" << sch[schIndex].second.second << '/' << item[sch[schIndex].second.first].second << "->"
            << (*it).first << '/' << (*it).second << endl;
        //cout << "day :" << (sch[schIndex].first % DUE +1) << endl;
        if(sch[schIndex].second.second == 0) //case1.empty space
        {
            sch[schIndex].first = schIndex;//sch_index
            sch[schIndex].second.first = (*index);//item_index
            sch[schIndex].second.second = (*it).first;//reward
            cout << "Machine(" << i+1 << ") receive :" << (*it).first << " on " << schIndex+1 << endl;
            return true;
        }
        //case2. better switching
        /*
          * condition1 : same reward?
          * condition2 : not same element?
          * condition3 : lower due than the original?
        */
        /*
        else if(sch[schIndex].second.second == (*it).first
              &&item[sch[schIndex].second.first].second > (*it).second
              &&(sch[schIndex].first % DUE +1) == (*it).second)
        {
            cout << "************ Better SWitching occur **********" << endl;
            cout << "Change :" << sch[schIndex].second.second << '/' << item[sch[schIndex].second.first].second << "->"
                << (*it).first << '/' << (*it).second << endl;
            cout << "index :" << schIndex << endl;
            item.push_back(make_pair(sch[schIndex].second.second, item[sch[schIndex].second.first].second));
            sch[schIndex].first = schIndex;//sch_index
            sch[schIndex].second.first = (*index);//item_index
            sch[schIndex].second.second = (*it).first;//reward
            //cout << "Machine(" << i+1 << ") receive :" << (*it).first << " on " << schIndex+1 << endl;
            return true;
        }
        */
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
            int schIndex=i*DUE+item_due;
            cout << "\nMachine(" << i+1 << ") refuse :" << (*it).first << " on " << schIndex+1 << endl;
            if(sch[schIndex2].second.second == 0)
            {
                cout << ">> Machine(" << i+1 << ") receive :" << (*it).first << " on " << schIndex2+1 << endl;
                sch[schIndex2].first = schIndex2;
                sch[schIndex2].second.first = (*index);
                sch[schIndex2].second.second = (*it).first;
                return;
            }
            else{;}//cout << "=>No space(already full) " << endl;}
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

    /* print nonBestItem*/
    for(vector<int>::iterator it=nonBestItem.begin();
        it!=nonBestItem.end(); ++it)
        {
          cout << item[*it].first << '/' << item[*it].second << ' ';
        }
    cout << endl;
    //Best_list sorting
    sort(sch.begin(), sch.end(), sortBy3);//ordery by reward

    /* Redefine
      * the 3rd is changed
      * scheduleType = schedule || item_index || the diff(=bestReward - secondReward)
    */
    scheduleType diff;
    //case1
    //substaction
    cout << "case1.substraction " << endl;
    unsigned int subtract=sch.size()-1;
    for(; subtract>0 &&sch[subtract].second.second==0; --subtract);
    cout << ">> target item(schInd/itemInd/reward) :" << sch[subtract].first << '-'<<  sch[subtract].second.first << '-' <<  sch[subtract].second.second << endl;
    diff.push_back(make_pair(subtract, make_pair(-1, sch[subtract].second.second)));

    //case2
    //surplus index
    cout << "case2.adding " << endl;
    for(scheduleType::iterator it=sch.begin();
        it!=sch.end(); ++it)
        {
            int schIndex=(*it).first,
                itemIndex=(*it).second.first,
                bestReward=(*it).second.second;
            int target_due=schIndex%DUE+1;
            cout << "\ntarget :" << '(' << schIndex << ')' << bestReward << '/' << target_due << " on " << itemIndex << " item index " << endl;
            //In the nonBestItem
            for(vector< int >::iterator nit=nonBestItem.begin();
                nit!=nonBestItem.end(); ++nit)
                {
                    //cout << " -- target switching start -- " << endl;
                    int i=(*nit);
                    int secondReward=item[i].first, secondDue=item[i].second;
                    //cout << "target_due :" << target_due << ", secondDue :" <<  secondDue << endl;
                    cout << ">> nonBest item :" << secondReward << '/' << secondDue << endl;
                    if(target_due <= secondDue
                      &&bestReward!=secondReward) //)Can be answer Answer
                    {
                        cout << ">> Done: best(" << schIndex << "):" << itemIndex << "->" << i << endl;
                        int _diff=bestReward - secondReward;
                        cout << ">> diff : " << _diff << endl;
                        if(_diff > 0) diff.push_back(make_pair(schIndex, make_pair(i, _diff)));
                        //break;
                    }
                }
        }
    //Print diff
    sort(diff.begin(), diff.end(), sortBy2);
    schPrint(diff);

    //setting the schedule_2nd
    if(diff[0].second.first == -1) //case1 -> Delete
    {
        int sub_index=sch[subtract].first;
        cout << "substraction execute " << endl;
        cout << "index :" << subtract << endl;
        secondBest[sub_index].first=sub_index;
        secondBest[sub_index].second.first=-1;
        secondBest[sub_index].second.second=0;
    } else // case2 -> Switching
    {
        cout << "adding execute " << endl;
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
              cout << '(' << (*it).first << ')' << (*it).second.second << '/' << (*it).second.first << ' ';//reward - itemIndex
              src.push_back((*it).second.first);//push the 'item' indexes from 'bestSchedule'
            }
        }
    cout << endl;
    //set dst
    cout << "item_size :" << item.size() << endl;
    for(unsigned i=0; i<item.size(); ++i)
    {
        vector< int >::iterator _find=find(src.begin(), src.end(), i);
        if(_find == src.end())
        {
          dst.push_back(i);
          //cout << '\n' << item[i].first << '/' << item[i].second << endl;
        } else{;}
    }
}

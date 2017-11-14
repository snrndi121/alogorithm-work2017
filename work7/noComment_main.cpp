#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

typedef pair < int, int > pType;
typedef pair < int, pType> lType;
vector < pType > weight;
vector < lType > location;
stack < int > answer;
int min_cost=0, totalWeight=1;

void fileread(void);
void filewrite(void);
void Init_Input(void);
bool sort1(pType& a, pType& b) {return a.first < b.first;}
bool sort2(lType& a, lType& b) {return a.first < b.first;}
void printStack(stack < int > src);
void printVector(vector < int >& src);
bool bounding(int _stand, int now_cost);
void InitRoad(stack < int >& src);
int findTarget(vector < int >& src, int _target);
void stackClear(stack < int >& src);
void stackClear(void);
void printAnswer(void);
int calCost(int src, int dst, int& totalWeight);
int calCostBack(int src, int dst, int _weight);
int calDistance(int src, int dst);
void searchRoad(void);
int main(void)
{
    fileread();
    Init_Input();

    searchRoad();
    printAnswer();

    return 0;
}
void fileread()
{
  ifstream ifs("drone.inp");
  int h, w, x, y;
  if(ifs.fail())
  {
      cout << "there's no file" << endl;
      return ;
  }
  int temp = 0;
  ifs >> temp;
  while(!ifs.eof())
  {
      ifs >> h >> w >> x >> y;
      weight.push_back(make_pair(h, w));
      location.push_back(make_pair(h, make_pair(x ,y)));
  }
  ifs.close();
}
void filewrite()
{
    ofstream ofs("drone.out");
    ofs << min_cost;
    ofs.close();
}
void printStack(stack < int > src)
{
    cout << "\nstack : ";
    if(src.size() == 0)
    {
        cout << "none" << endl;
        return ;
    }
    while(!src.empty())
    {
        int _top=src.top();
        src.pop();
        cout << _top << ' ';
    }
    cout << endl;
}
void printVector(vector < int >& src)
{
    cout << "\ntemp : ";
    if(src.size() == 0)
    {
        cout << "none" << endl;
        return ;
    }
    for(vector < int >::iterator it=src.begin();
        it!=src.end(); ++it)
        {
            cout << (*it) << ' ';
        }
    cout << endl;
}
void Init_Input(void)
{
    sort(weight.begin(), weight.end(), sort1);
    sort(location.begin(), location.end(), sort2);
    cout << " >> Initializing weight" << endl;
    cout << " >> Initializing location" << endl;
    }
void InitRoad(stack < int >& src)
{
    int total_weight=1;
    answer=src;
    //initialize the stackRoad and total weight
    for(vector < pType >::iterator it=weight.begin();
        it!=weight.end(); ++it)
    {
        src.push((*it).first);
        total_weight+=(*it).second;
    }
    //calculate the initial cost
    totalWeight=total_weight;
    for(unsigned int i=0; i<src.size(); ++i)
    {
        min_cost+=calCost(i, i+1, total_weight);
    }
    cout << "Init_cost :" << min_cost << endl;
}
int findTarget(vector < int >& src, int _target)
{
    int index=0;
    for(vector < int >::iterator it=src.begin();
      it!=src.end(); ++it)
      {
          if((*it) > _target)
          {
              return index;
          }
          index++;
      }
      return -1;
}
void stackClear(void)
{
    for(unsigned int i=0; i<answer.size(); ++i)
    {
        answer.pop();
    }
}
void stackClear(stack < int >& src)
{
    for(unsigned int i=0; i<src.size() ;++i)
    {
        src.pop();
    }
}
void printAnswer(void)
{
    cout << ">> answer stack : ";
    while(!answer.empty())
    {
        cout << answer.top() << ' ';
        answer.pop();
    }
    cout << "\n>> min_cost : " << min_cost << endl;
    cout << endl;
}
int calDistance(int srcInd, int dstInd)
{
    int dis_x=abs(location[srcInd].second.first-location[dstInd].second.first);
    int dis_y=abs(location[srcInd].second.second-location[dstInd].second.second);
    return dis_x + dis_y;
}
int calCost(int srcIndex, int dstIndex, int& _total_weight)
{
    int dis=calDistance(srcIndex, dstIndex % location.size());
    int dropWeight=weight[srcIndex].second;
    _total_weight-=dropWeight;
    return _total_weight*dis;
}
int calCostBack(int srcIndex, int dstIndex, int _weight)
{
    int _dis=calDistance(srcIndex, dstIndex % location.size());
    int _cost=0;
    _cost=_weight * _dis;
    return _cost;
}
bool bounding(int _stand, int now_cost)
{
    return _stand < now_cost;
}
void searchRoad(void)
{
    stack < int > stackRoad;
    vector < int > temp;
    InitRoad(stackRoad);
    int returnCost1=calCostBack(stackRoad.top()-1, 0, 1), returnCost2=0;
    int new_cost=min_cost-returnCost1;
    int _weight=1;
    clock_t start=clock(), end=0;
    while(!stackRoad.empty())
    {
        int _top=stackRoad.top();
        //printStack(stackRoad);
        int _new_top=findTarget(temp, _top);
        // Switching the top biggenr than current top
        // And pushing all from temp into stackRoad
        if(_new_top != -1)
        {
            //selecting the top bigger than current top
            //action_1 : pop a origin Top
            stackRoad.pop();
            if(stackRoad.empty()) {break;}
            temp.push_back(_top);
            _weight+=weight[_top-1].second;
            int _beforeTop=stackRoad.top();
            new_cost-=calCostBack(_top-1, _beforeTop-1, _weight);

            //printStack(stackRoad);
            //action_2 : switch a new Top
            stackRoad.push(temp[_new_top]);
            new_cost+=calCostBack(_beforeTop-1, temp[_new_top]-1, _weight);
            _weight-=weight[temp[_new_top]-1].second;
            temp.erase(temp.begin() + _new_top);
            //printStack(stackRoad);

            // !the temp must be sorted by desc
            sort(temp.begin(), temp.end());
            //action_3 : pushing all from the temp into stackRoad
            for(vector < int >::iterator it=temp.begin();
                it!=temp.end(); ++it)
                {
                    _beforeTop=stackRoad.top();
                    stackRoad.push((*it));
                    new_cost+=calCostBack(_beforeTop-1, (*it)-1, _weight);
                    _weight-=weight[(*it)-1].second;
                    //printStack(stackRoad);
                }
            temp.clear();
            returnCost2=calCostBack(stackRoad.top()-1, 0, 1);
            //printVector(temp);
        } else
        {
            stackRoad.pop();
            temp.push_back(_top);//con1
            _weight+=weight[_top-1].second;///con2
            new_cost-=calCostBack(_top-1, stackRoad.top()-1, _weight);
            //printStack(stackRoad);
            sort(temp.begin(), temp.end());
        }
        if(temp.size() == 0 && min_cost> new_cost+returnCost2)
        {
            min_cost=new_cost+returnCost2;
            stackClear();
            answer=stackRoad;
        }
    }
    end=clock();
    cout << ">> time : " << (end-start)/CLOCKS_PER_SEC << endl;
}

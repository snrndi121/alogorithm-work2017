#include <iostream>
#include <fstream>
#include <algorithm>
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
/*
template < type T >
bool sort3(T& a, T& b) {return a.first < b.first;}
*/
bool sort1(pType& a, pType& b) {return a.first < b.first;}
bool sort2(lType& a, lType& b) {return a.first < b.first;}
void printStack(stack < int > src);
void printVector(vector < int >& src);
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

    //print
    cout << "\n---- Weight ----" << endl;
    for(vector < pType >::iterator it=weight.begin();
        it!=weight.end(); ++it)
        {
            cout << (*it).first << ' ' << (*it).second << endl;
        }
    cout << "\n---- Location ----" << endl;
    for(vector < pair < int, pType > >::iterator it=location.begin();
        it!=location.end(); ++it)
        {
              cout << (*it).first << ": (" << (*it).second.first << ", " << (*it).second.second << ')' << endl;
        }
    cout << endl;
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
    cout << "cost :" << min_cost << endl;
}
int findTarget(vector < int >& src, int _target)
{
    int index=0;
    for(vector < int >::iterator it=src.begin();
      it!=src.end(); ++it)
      {
          if((*it) > _target)
          {
              //src.erase(it);
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
    cout << endl << endl << ">> answer stack : ";
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
    cout << "\nbetween src -dst(" << srcIndex+1 << '-' << dstIndex+1 << ") :"<< dis << endl;
    //cout << "src(" << srcIndex+1 <<  ") -> dst(" << dstIndex+1 << ") :" << dis << endl;
    int dropWeight=weight[srcIndex].second;
    //cout << ">> dropping :" << dropWeight << endl;
    _total_weight-=dropWeight;
    return _total_weight*dis;
}
int calCostBack(int srcIndex, int dstIndex, int _weight)
{
    cout << "\n< Operation : calCostback start > " << endl;
    int _dis=calDistance(srcIndex, dstIndex % location.size());
    int _cost=0;
    cout << ">> D :" << _dis << " (" << srcIndex+1 << "->" << dstIndex+1 << ")" << endl;
    cout << ">> W :" << _weight << endl;
    _cost=_weight * _dis;
    cout << ">> cost's generated : " << _cost << endl << endl;
    return _cost;
}
void searchRoad(void)
{
    stack < int > stackRoad;
    vector < int > temp;
    InitRoad(stackRoad);
    int returnCost1=calCostBack(stackRoad.top()-1, 0, 1), returnCost2=0;
    cout << " >> Init_return cost :" << returnCost1 << endl;
    int new_cost=min_cost-returnCost1;
    int index=0;
    int _weight=1;
    while(!stackRoad.empty() && index < 400)
    {
        int _top=stackRoad.top();
        cout << "\n\n(" << index++ << ")";
        printStack(stackRoad);
        cout << "\n>> current min_cost :" << min_cost << endl;
        cout << ">> weight : " << _weight << endl;
        int _new_top=findTarget(temp, _top);
        // Switching the top biggenr than current top
        // And pushing all from temp into stackRoad
        if(_new_top != -1)
        {
            //selecting the top bigger than current top
            //action_1 : pop a origin Top
            cout << "\nop(1): pop the top --- " << endl;
            stackRoad.pop();int _beforeTop=stackRoad.top();
            temp.push_back(_top);
            _weight+=weight[_top-1].second;
            new_cost-=calCostBack(_top-1, _beforeTop-1, _weight);
            cout << "op(2): After pop -- " << endl;
            cout << ">> new weight :" << _weight << endl;
            cout << ">> pending cost :" << new_cost << endl;
            printStack(stackRoad);
            //printVector(temp);

            //action_2 : switch a new Top
            stackRoad.push(temp[_new_top]);
            new_cost+=calCostBack(_beforeTop-1, temp[_new_top]-1, _weight);
            _weight-=weight[temp[_new_top]-1].second;
            cout << "op(3): After switching -- " << endl;
            cout << ">> new weight :" << _weight << endl;
            cout << ">> pending cost :" << new_cost << endl;

            temp.erase(temp.begin() + _new_top);
            printStack(stackRoad);

            // !the temp must be sorted by desc
            cout << "\nop(4): pushing all from the temp into stackRoad -- " << endl;
            sort(temp.begin(), temp.end());
            //action_3 : pushing all from the temp into stackRoad
            for(vector < int >::iterator it=temp.begin();
                it!=temp.end(); ++it)
                {
                    _beforeTop=stackRoad.top();
                    stackRoad.push((*it));
                    new_cost+=calCostBack(_beforeTop-1, (*it)-1, _weight);
                    _weight-=weight[(*it)-1].second;

                    cout << "op(5): After pushing -- " << endl;
                    cout << ">> new weight :" << _weight << endl;
                    cout << ">> pending cost :" << new_cost << endl;
                    printStack(stackRoad);
                }
            temp.clear();
            returnCost2=calCostBack(stackRoad.top()-1, 0, 1);
            cout << ">> new return cost(" << stackRoad.top() << "-> 1): " << returnCost2 << endl;
            cout << ">> Thus the total cost is :" << new_cost << '+' << returnCost2 << '=' << new_cost + returnCost2 << endl;
            //printVector(temp);
        } else
        {
            cout << "\nop(*): temp empty or dont has it" << endl;
            stackRoad.pop();
            temp.push_back(_top);//con1
            _weight+=weight[_top-1].second;///con2
            new_cost-=calCostBack(_top-1, stackRoad.top()-1, _weight);
            cout << "op(**): After pop -- " << endl;
            cout << ">> new weight :" << _weight << endl;
            cout << ">> pending cost :" << new_cost << endl;
            printStack(stackRoad);
            sort(temp.begin(), temp.end());
        }
        if(temp.size() == 0 && min_cost> new_cost+returnCost2)
        {
            min_cost=new_cost+returnCost2;
            stackClear();
            answer=stackRoad;
            cout << ">> the new_cost is updated :" << min_cost << endl;
        }
        else cout << ">> The new_cost cannot be selected." << endl;
    }
}

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

//Init data variable
typedef pair < int, int > pType;
typedef pair < int, pType > lType;
typedef pair < pType, int > vType;
vector < pType > weight;
vector < lType > location;


//Clustering
class kMCluster
{
public:
  kMCluster(int _k) {
    this->CTindex=0;
    this->kMeans=_k;
    for(vector <lType>::iterator it=location.begin();
        it!=location.end(); ++it)
    {
        CPoint.push_back(make_pair((*it).second.first, (*it).second.second));
    }
  }
  void Init(void)
  {
      initCenter();
      initSet();
  }
  void initCenter(void)
  {
      srand((unsigned int)time(NULL));
      int _size=location.size();
      for(int i=0; i<kMeans; ++i)
      {
        int t=rand()%_size;
        cout << ">> rand_index :" << t << endl;
        CCenter.push_back(make_pair(CTindex, t));
      }
  }
  void initGroup(void)
  {
      for(unsigned int i=0; i<CPoint.size(); ++i)
      {
          int _sIndex=0;
          int d1=getDistance(i, 0);
          for(int j=1; j<kMeans; ++j)
          {
              int d2=getDistance(i, j);
              if(d1 > d2)   //judge setIndex;
              {
                  _sIndex=d2;
              }
          }
          //define
          CSet.push_back(make_pair(make_pair(CTindex, _sIndex), i));
      }
      cout << ">> cset :" << CSet.size() << endl;
  }
  bool checkSame(vector < pType>& _CNew)
  {


  }
  void adjustCenter(vector < pType >& _CNew)
  {
      int _tindex=CTindex+1;
      for(int s=0; s<kMeans; ++s)
      {
          int _snum=
          for(int m=0; m<_sum; ++m)
          {

          }
      }
  }
  void adjustSet(vector < pType >& _CNew)
  {

  }
  int getDistance(int _src, int _dst)
  {   //Manhaton distance
      int dis_x=abs(CPoint[_src].first-CPoint[_dst].first);
      int dis_y=abs(CPoint[_src].second-CPoint[_dst].second);
      return dis_x + dis_y;
  }
  void Clear(void) {
      this->kMeans=0;
      CSet.clear();
      CCenter.clear();
  }
private:
    int kMeans;
    int CTindex;
    vector < pType > CPoint;//int point_x ||int point_y
    vector < pType > CCenter;//int tindex ||int point_index
    vector < vType > CSet;//int tinder ||int set_index || vector_set_member
};

void fileread(void);
void findway(kMCluster& kcluster);
void printanswer(void);
void kClustering(kMCluster& km);

int main(void)
{
    fileread();
    kMCluster km(2);
    kClustering(km);

    findway(km);
    printanswer();
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
void kClustering(kMCluster& km)
{
    cout << " - clustering - " << endl;
    //Initializing
    km.Init();//Init_center, Init_set

    /*
    while(checkSame(_CNew))
    {
        vector < pType > _CNew;
        adjustCenter(_CNew);
        adjustSet(_CNew);
    }
    */
}
void findway(kMCluster& kCluster)
{
    cout << " - findWay start - " << endl;
}
void printanswer(void)
{
    cout << " - print answer - " << endl;
}

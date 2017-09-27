#include "oil.h"
#include <iostream>
#include <cmath>
using namespace std;

#define MIN_OIL 10
#define MAX_OIL 100000

void err_oilSize(int _size);
int range_check(int _start, int _end, int _target);
void find_oil(int _begin, int _end, int which); //find oil sector
void update_oil(int _begin, int _end); //update oil_begin, oil_end

//define oil begin, end
int ans_begin=0, ans_end=0;

int main(void)
{
  initial();

  int szOil=oil_size();
  err_oilSize(szOil);
  //observe
  /*
    -1 : error
     0 : Empty
     1 : series of 1
     2 : mixed 0 and 1
  */
  cout << "begin :" << ans_begin << ", " << "end :" << ans_end << endl;
  find_oil(ans_begin, szOil-1, 0);
  oil_report(ans_begin, ans_end);
  return 0;
}

void err_oilSize(int _size)
{
  if(_size < MIN_OIL || _size > MAX_OIL)
      cout << "\n>> Size error occured !!" << endl;
}
int range_check(int _target)
{
    if(ans_begin <=_target && ans_end >=_target) //In
        return -1;
    else if(_target < ans_begin)  //left side
        return 0;
    else    //right side
        return 1;

}
void update_oil(int new_begin, int new_end)
{
    cout << "now begin :" << ans_begin << ", " << "end : " << ans_end << endl;
    cout << "new begin :" << new_begin << ", " << "end : " << new_end << endl;
    cout << endl;
    int begin_rchk=range_check(new_begin),
        end_rchk=range_check(new_end);
    if(begin_rchk == -1)
    {
        //new_begin in
        //if(end_rchk == -1){;}
        //if(end_rchk == 0){;}
        if(end_rchk == 1){ans_end=new_end;}
    }
    else if(begin_rchk == 0)
    {
        ans_begin=new_begin;
        //if(end_rchk == -1){;}
        //if(end_rchk == 0){;}
        if(end_rchk == 1){ans_end=new_end;}
    }
    else
    {
        if(ans_begin ==0 && ans_end ==0)
            ans_begin=new_begin;
        //if(end_rchk == -1){;}
        //if(end_rchk == 0){;}
        if(end_rchk == 1){ans_end=new_end;}
    }
}
void find_oil(int _begin, int _end, int which)
{
    if(ans_end <=_begin && ans_end >= _end)
        return ;
    if(_begin == _end && _begin > _end)
        return ;
    int mid=(_begin + _end)/2;
    int lbeg=_begin, lend=mid;
    int rbeg=mid+1, rend=_end;

    int rchk=observe(_begin, _end);
    cout << "rchk :" << rchk << endl;
    if(rchk == -1)
        return ;
    else if(rchk == 0)
        cout << "no oil" << endl;
    else if(rchk == 1)
    {
        if(which == 0)
            update_oil(rbeg, rend);
        else
            update_oil(lbeg, lend);
    }
    else
    {
        cout << "l: lbegin :" << lbeg << ", " << "lend :" << lend << endl;
        find_oil(lbeg, lend, 0);
        cout << "r: rbegin :" << rbeg << ", " << "rend :" << rend << endl;
        find_oil(rbeg, rend, 1);
    }
}

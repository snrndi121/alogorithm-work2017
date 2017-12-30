#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>
#include <string>

using namespace std;

/* global variable */
unsigned int k=0;
string mother_chrome;
map < string, pair < string, int > > table;
struct hType
{
    hType() {token = "", count = 0;}
    string token;
    unsigned count=0;
};
typedef struct hType hType;
void file_read(void);
hType MFK_map(void);
void stringFound(void);
hType heapsort(void);
void print_answer(hType mfk);

struct cmp{
   bool operator()(hType& a, hType& b)
   {
      return a.count < b.count;//(a.hval < b.hval) && (a.p.first < b.p.first);//
   }
};
typedef struct cmp cmp;

int main(void)
{
    file_read();

    print_answer(MFK_map());

    return 0;
}
void file_read(void)
{
    ifstream ifs("k-mer.inp");
    string str;
    ifs >> k;
    while(ifs >> str)
    {
        mother_chrome += str;
    }
    ifs.close();
}
hType MFK_map(void)
{

    stringFound();
    hType _mfk = heapsort();
    return _mfk;
}
hType heapsort(void)
{
    priority_queue < hType, vector < hType >, cmp > pq;
    map < string, pair < string, int > >::iterator it = table.begin();
    hType _h;
    for(; it != table.end(); ++it)
    {
        _h.token = (*it).second.first;
        _h.count = (*it).second.second;
        pq.push(_h);
    }
    //check Dictionary order
    hType _ans = pq.top(), _compare;
    pq.pop();
    _compare = pq.top();
    cout << "now top\n" << _ans.token << endl;
    cout << "(" << _compare.count << ")" << _compare.token << endl;
    while(_ans.count == _compare.count)
    {
        //compare
        if(_ans.token > _compare.token)
        {
          cout << " >> changing" << endl;
          _ans=_compare;
        }
        pq.pop();
        _compare = pq.top();
        cout << "(" << _compare.count << ")" << _compare.token << endl;
    }
    return _ans;
}
void stringFound(void)
{
    //cout << "\n>> src_string : " << chrome[_index] << endl;
    string next_string = mother_chrome.substr(0, k);
    //cout << "neew_tooken :" << next_string << endl;
    for(unsigned i=k; i <= mother_chrome.size(); ++i)
    {
        if(table.find(next_string) != table.end())
            ++table[next_string].second;
        else
            table.insert(make_pair(next_string, make_pair(next_string, 1)));
        if(i != mother_chrome.size())
        {
            next_string.erase(next_string.begin());
            next_string += mother_chrome[i];
        }
        //cout << "next_string :" << next_string << endl;
    }
}
void print_answer(hType mfk)
{

  ofstream ofs("k-mer.out");
  ofs << mfk.token;
  ofs.close();
}

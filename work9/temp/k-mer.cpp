#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>
#include <string>

using namespace std;

/* global variable */
unsigned const int base=256;
unsigned int k=0;
vector < string > chrome;
map < string, pair < string, int > > table;

struct hType
{
    string s;
    unsigned count=0;
};
typedef struct hType hType;

void file_read(void);
void printAnswer(void);
void MFK_map(void);
void stringFound(string& s);
void Quicksort3way(vector < string >& a);
void qsort3way(vector < string >& a, int l, int h, int d);
struct cmp1{
   bool operator()(hType& a, hType& b)
   {
      return a.count < b.count;//(a.hval < b.hval) && (a.p.first < b.p.first);//
   }
};
typedef struct cmp1 cmp1;
void heapsort1(void)
{
  priority_queue <hType, vector<hType>, cmp1 >pq;
  map < string, pair < string, int > >::iterator it=table.begin();
  hType _h;
  for(; it!=table.end(); ++it)
  {
      _h.s=(*it).second.first;
      _h.count=(*it).second.second;
      pq.push(_h);
  }
  //check Dictionary order
  hType _ans=pq.top(), _compare;
  pq.pop();
  _compare=pq.top();
  //cout << "now top\n" << _ans.s << endl;
  //cout << "(" << _compare.count << ")" << _compare.s << endl;
  while(_ans.count == _compare.count)
  {
      //compare
      if(_ans.s > _compare.s)
      {
        //cout << " >> changing" << endl;
        _ans=_compare;
      }
      pq.pop();
      _compare=pq.top();
      //cout << "(" << _compare.count << ")" << _compare.s << endl;
  }
  ofstream ofs("k-mer.out");
  ofs << _ans.s;
  ofs.close();
}
int main(void)
{
    file_read();

    MFK_map();

    heapsort1();
    return 0;
}
void file_read(void)
{
    ifstream ifs("k-mer.inp");
    string str;
    ifs >> k;
    while(ifs >> str)
    {
        chrome.push_back(str);
    }
    ifs.close();
}
void printAnswer(void)
{
    ofstream ofs("k-mer.out");
    map< string, pair < string, int > >::iterator it=table.begin();
    map< string, pair < string, int > >::iterator end_it=table.end();
    string end=chrome[chrome.size()-1];
    pair < string, int > ans=make_pair(end, 0);

    for(; it!=end_it; ++it)
    {
        if(ans.second < (*it).second.second)
        {
            ans=(*it).second;
        }
        else if(ans.second == (*it).second.second && ans.first) > (*it).second.first)
        {
            ans=(*it).second;
        }else{;}
    }
    ofs << ans.first << endl;
    ofs.close();
}
// 3-Way Quicksort
void Quicksort3way(vector < string >& a)
{
    int len=a.size()-1;
		qsort3way(a, 0, len, 0);
}
// helper method for 3 way quicksort
void swap(vector < string >& a, int i, int j)
{
		string temp = a[i];
		a[i] = a[j];
		a[j] = temp;
}
void qsort3way(vector < string >& a, int l, int h, int d)
{
		if (h <= l) return;

		int lt = l, gt = h;
		int v = a[l][d];
		int i = l + 1;

		// partition
    while(i <= gt)
    {
        int t = a[i][d];
        if(t < v) { swap(a, lt++, i++); }
        else if(t > v) { swap(a, i, gt--);}
        else { i++; }
    }
		// a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]
		qsort3way(a, l, lt - 1, d);
		if(v >= 0) { qsort3way(a, lt, gt, d + 1); }
		qsort3way(a, gt + 1, h, d);
}
void stringFound(int _index)
{
    //cout << "\n>> src_string : " << chrome[_index] << endl;
    string next_string=chrome[_index].substr(0, k);
    //cout << "neew_tooken :" << next_string << endl;
    for(unsigned i=k; i <= chrome[_index].size(); ++i)
    {
        if(table.find(next_string) != table.end())
            ++table[next_string].second;
        else
            table.insert(make_pair(next_string, make_pair(next_string, 1)));
        if(i != chrome[_index].size())
        {
            next_string.erase(next_string.begin());
            next_string+=chrome[_index][i];
        }
        //cout << "next_string :" << next_string << endl;
    }
}
void stringFound(string& s)
{
    //cout << "\n>> src_string : " << chrome[_index] << endl;
    string next_string=s.substr(0, k);
    //cout << "neew_tooken :" << next_string << endl;
    for(unsigned i=k; i <= s.size(); ++i)
    {
        if(table.find(next_string) != table.end())
            ++table[next_string].second;
        else
            table.insert(make_pair(next_string, make_pair(next_string, 1)));
        if(i != s.size())
        {
            next_string.erase(next_string.begin());
            next_string+=s[i];
        }
        //cout << "next_string :" << next_string << endl;
    }
}
void MFK_map(void)
{
  string mother_chrome;
  vector < string >::iterator it=chrome.begin();
  vector < string >::iterator end_it=chrome.end();
  for(;it!=end_it;++it)
      mother_chrome+=(*it);
  stringFound(mother_chrome);
}
unsigned long long hashString(string& s)
{
    unsigned long long firstXLengthSubString = 0;
    unsigned int i;
    for(i = 0; i < k; ++i)
    {
        firstXLengthSubString *= base;
        firstXLengthSubString += s[i];
    }
    return firstXLengthSubString;
}

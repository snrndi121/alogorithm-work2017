#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

/* global variable */
unsigned const int base=256;
unsigned int k=0, N=0;
vector < string > chrome;
map < string, pair < string, int > > table;

void file_read(void);
void printAnswer(void);
void MFK_map(void);
void Quicksort3way(vector < string >& a);
void qsort3way(vector < string >& a, int l, int h, int d);
void countTotalToken(void);
unsigned long long hashString(string& s);

int main(void)
{
    file_read();
    MFK_map();
    Quicksort3way(chrome);
    printAnswer();
    //countTotalToken();
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
void countTotalToken(void)
{
    for(unsigned i=0; i<chrome.size(); ++i)
    {
        N += chrome[i].size() - k + 1;
    }
    cout << "N :" << N << endl;
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
        else if(ans.second == (*it).second.second && ans.first >(*it).first)
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
    static unsigned count_token=0;
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
            count_token++;
            next_string.erase(next_string.begin());
            next_string+=chrome[_index][i];
        }
        //cout << "next_string :" << next_string << endl;
    }
    if((unsigned)_index + 1 == chrome.size())
        cout << "cout_token :" << count_token << endl;
}
void printTable(void)
{
      map < string, pair < string, int > >::iterator it=table.begin();
      map < string, pair < string, int > >::iterator end_it=table.end();
      for(; it!=end_it; ++it)
      {
          cout << '(' << (*it).second.second << ")token : " << (*it).second.first  << endl;
      }
}
void MFK_map(void)
{
  int target_index=0;
  for(vector < string >::iterator sit=chrome.begin(); sit!=chrome.end(); sit++)
  {
      stringFound(target_index);
      target_index++;
  }
  //printTable();
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

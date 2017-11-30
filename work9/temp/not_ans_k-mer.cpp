#include <iostream>
#include <fstream>
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/* global variable */
unsigned int k=0;  //len of chrome
vector < string > chrome;
typedef pair <int, int> pType;
//typedef pair < int, pair < int, int > > ppType; //count || string index || K token start index
map<unsigned long long, pType > hashTable;//< hash, pair < count, start index > >
unsigned const int base = 256;
unsigned long long xPowOfBase = 1;

struct hType
{
    unsigned long long int hval;
    pType p;
};
typedef hType hType;

struct cmp1{
   bool operator()(hType& a, hType& b)
   {
      return a.p.first < b.p.first;//(a.hval < b.hval) && (a.p.first < b.p.first);//
   }
};
typedef struct cmp1 cmp1;

void file_read(void);
void printAnswer(string& s);
void printTable();
string MFK_hash(void);
string heapsort1(string s);
int main(void)
{
    file_read();

    //Quicksort3way(chrome);

    string ans=MFK_hash();

    printAnswer(ans);
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
void printAnswer(string& s)
{
    ofstream ofs("k-mer.out");
    ofs << s;
    ofs.close();
}
void hash_count(string& s)
{
  unsigned const int base = 256; //Means that 1 bit -> 2^8 integer
  unsigned long long xPowOfBase = 1;
  unsigned int i = 0;
  for(i = 1; i <= k; ++i)
      xPowOfBase *= base;//Means that token(x) has xPowOfBase x bit <-> x*2^8 integer

  //step1.hashing :
  //Init first substring(0 ~ k(delimeter))
  unsigned long long firstXLengthSubString = 0;
  for(i = 0; i < k; ++i)
  {
      firstXLengthSubString *= base;
      firstXLengthSubString += s[i];
  }

  unsigned long long nextXLengthSubstring = firstXLengthSubString;

  //step2.start i = k + 1 until total string s.
  for(;i <= s.size(); ++i)
  {
      //find nextSubstring then count up
      if(hashTable.find(nextXLengthSubstring) != hashTable.end())
          ++hashTable[nextXLengthSubstring].first;
      //Not found then nextSubstring and Init value
      else
          hashTable.insert(std::make_pair(nextXLengthSubstring, std::make_pair(1, i - k)));//[i-x] : means that find the start index

      //Index i < toal String s
      //Then change nextSubstring
      if(i != s.size())
      {
          nextXLengthSubstring *= base;
          nextXLengthSubstring += s[i];
          //Modify the start Index of substrings to be checked
          nextXLengthSubstring -= s[i - k] * xPowOfBase;
      }
  }

  //sorting
  std::map<unsigned long long, std::pair<int, int> >::iterator it = hashTable.begin();
  std::map<unsigned long long, std::pair<int, int> >::iterator end_it = hashTable.end();
  std::pair<int, int> maxCountAndFirstPosition = std::make_pair(0, -1);

  for(;it != end_it; ++it)
  {
      if(maxCountAndFirstPosition.first < it->second.first)
          maxCountAndFirstPosition = it->second;
  }

  std::cout << maxCountAndFirstPosition.first << std::endl;
  std::cout << s.substr(maxCountAndFirstPosition.second, k) << std::endl;
}
string MFK_hash(void)
{
  unsigned int i = 0;
  for(i = 1; i <= k; ++i)
      xPowOfBase *= base;//Means that token(x) has xPowOfBase x bit <-> x*2^8 integer

  string mother_chrome;
  vector < string >::iterator it=chrome.begin();
  vector < string >::iterator end_it=chrome.end();
  for(;it!=end_it;++it)
      mother_chrome+=(*it);
  hash_count(mother_chrome);
  string s=heapsort1(mother_chrome);
  return s;
}
string heapsort1(string s)
{
  priority_queue <hType, vector<hType>, cmp1 >pq;
  map<unsigned long long, pType>::iterator it;
  hType _h;
  for(it=hashTable.begin(); it!=hashTable.end(); ++it)
  {
      _h.hval=(*it).first;
      _h.p=(*it).second;
      pq.push(_h);
  }
  //check Dictionary order
  hType _ans=pq.top(), _compare;
  pq.pop();
  _compare=pq.top();
  cout << "now top\n" << s.substr(_ans.p.second, k) << endl;
  cout << "(" << _compare.p.second << ")" << s.substr(_compare.p.second, k) << endl;
  while(_ans.p.first == _compare.p.first)
  {
      //compare
      if(_ans.hval > _compare.hval)
      {
        cout << " >> changing" << endl;
        _ans=_compare;
      }
      pq.pop();
      _compare=pq.top();
      cout << "(" << _compare.p.first << ")" << s.substr(_compare.p.second, k) << endl;
  }
  return s.substr(_ans.p.second, k);
}

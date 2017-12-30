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
unsigned int N=0; // num of token
vector < string > chrome;
typedef pair <int, int> pType;
typedef pair < int, pair < int, int > > ppType; //count || string index || K token start index
map<unsigned long long, ppType > hashTable;//< hash, pair < count, start index > >
unsigned const int base = 256;
unsigned long long xPowOfBase = 1;

struct hType
{
    unsigned long long int hval;
    ppType p;
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
void printAnswer(void);
void printTable();
void MFK_hash(void);

int main(void)
{
    file_read();

    //Quicksort3way(chrome);

    MFK_hash();

    printAnswer();
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
    ppType ans=make_pair(0, make_pair(-1 ,0));
    map <unsigned long long, ppType >::iterator it=hashTable.begin();
    for(; it!=hashTable.end(); ++it)
    {
        cout << '(' << (*it).second.first << ')';
        cout << chrome[(*it).second.second.first].substr((*it).second.second.second, k) << endl;
        if(ans.first < (*it).second.first)
            ans = (*it).second;
    }
    cout << chrome[ans.second.first].substr(ans.second.second, k) << endl;
    ofs.close();
}
void hash_count(string& s)
{
    string s=chrome[sindex];
    unsigned long long nextXLengthSubstring = hashString(s);
    //step2.gen hash Token
    for(unsigned i=k; i <= s.size(); ++i)
    {
        //find nextSubstring then count up
        if(hashTable.find(nextXLengthSubstring) != hashTable.end())
            ++hashTable[nextXLengthSubstring].first;
        //Not found then nextSubstring and Init value
        else
        {
            hashTable.insert(make_pair(nextXLengthSubstring, make_pair(1, make_pair(sindex, i - k))));//[i-x] : means that find the start index
        }
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
    //cout << nextXLengthSubstring << endl;
}
void MFK_hash(void)
{
  unsigned int i = 0;
  for(i = 1; i <= k; ++i)
      xPowOfBase *= base;//Means that token(x) has xPowOfBase x bit <-> x*2^8 integer

  string mother_chrome;
  vector < string >::iterator it=chrome.begin();
  vector < string >::iterator end_it=chrome.end();
  for(;it!=end_it;++it)
      mother_chrome+=(*it);
  hash_count(tindex);
  heapsort1();
}
void heapsort1(void)
{
  priority_queue <hType, vector<hType>, cmp1 >pq;
  map<unsigned long long, ppType>::iterator it;
  hType _h;
  for(it=hashTable.begin(); it!=hashTable.end(); ++it)
  {
      _h.hval=(*it).first;
      _h.p=(*it).second;
      cout << "hash :" << _h.hval << endl;
      cout << "string :" << chrome[_h.p.second.first].substr(_h.p.second.second, k) << endl;
      cout << "count :" << _h.p.first << endl << endl;
      pq.push(_h);
  }
  //check Dictionary order
  hType _ans=pq.top(), _compare;
  pq.pop();
  _compare=pq.top();
  while(_ans.p.first == _compare.p.first)
  {
      //compare
      if(_ans.hval > _compare.hval)
      {
        _ans=_compare;
      }
      pq.pop();
      _compare=pq.top();
  }
  /*
  cout << " ---- hash collision ---- " << endl;
  cout << " A : aabaacc, B : ccaabaa" << endl;
  string A="aabaacc", B="ccaabaa";
  cout << ">> A.hashString(A) :" << hashString(A) << endl;
  cout << ">> B.hashString(B) :" << hashString(B) << endl;
  */
  cout << endl;
  cout << "token_size :" << k << endl;
  cout << "hash :" << _ans.hval << endl;
  cout << "count:" << _ans.p.first << endl;
  int target_index=_ans.p.second.first;//String index
  int start_index=_ans.p.second.second;//Start index
  cout << " >> target_index :" << target_index << endl;
  cout << " >> start_index :" << start_index << endl;
  cout << "mother string :" << chrome[target_index] << endl;
  cout << " >> token :" << chrome[target_index].substr(start_index, k) << endl;
  printHashInfo(_ans.hval);
}
void printHashInfo(unsigned long long& _hval)
{
    cout << "\n ---- hashTable Info -----" << endl;
    cout << ">> HashTable_count :" << hashTable[_hval].first << endl;
    cout << ">> HashTable_string :" << chrome[hashTable[_hval].second.first].substr(hashTable[_hval].second.second, k) << endl;
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

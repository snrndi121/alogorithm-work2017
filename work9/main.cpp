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

struct hType
{
    unsigned long long int hval;
    ppType p;
};typedef hType hType;

struct cmp{
   bool operator()(ppType& a, ppType& b)
   {
      return a.first < b.first;
   }
};typedef struct cmp cmp;

struct cmp1{
   bool operator()(hType& a, hType& b)
   {
      return a.p.first < b.p.first;//(a.hval < b.hval) && (a.p.first < b.p.first);//
   }
};typedef struct cmp1 cmp1;

void file_read(void);
void printAnswer(void);
void printVector(vector < string >& str);
void printHashInfo(unsigned long long& _hval);
void Quicksort3way(vector < string >& a);
void swap(vector < string >& a, int i, int j);
void qsort3way(vector < string >& a, int l, int h, int d);
void hashCount(string& s, unsigned int sindex, unsigned long long& xPowOfBase);
void heapsort(void);
void heapsort1(void);
unsigned long long hashString(string& s);
void MFK_hash(void);

int main(void)
{
    file_read();
    //printVector(chrome);

    Quicksort3way(chrome);
    //printVector(chrome);

    MFK_hash();
    //printAnswer();
    return 0;
}
void file_read(void)
{
    ifstream ifs("k-mer.inp");
    ifs >> k;
    while(!ifs.fail())
    {
        string str;
        ifs >> str;
        chrome.push_back(str);
    }
    ifs.close();
}
void printAnswer(void)
{
    //cout << maxCountAndFirstPosition.first << std::endl;
    //cout << s.substr(maxCountAndFirstPosition.second, x) << std::endl;
    ofstream ofs("k-mer.out");

    ofs.close();
}
void printVector(vector < string >& str)
{
    for(vector < string >::iterator it=str.begin();
        it!=str.end(); ++it)
    {
        cout << (*it) << endl;
    }
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
//Maybe you can get rid of parameter s here using global variable 'chrome' and its 'sindex'
void hash_count(string& s, unsigned int sindex, unsigned long long& xPowOfBase)
{
    unsigned int i;
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
            hashTable.insert(make_pair(nextXLengthSubstring, make_pair(1, make_pair(sindex, i - k))));//[i-x] : means that find the start index
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
}
void MFK_hash(void)
{
  unsigned const int base = 256; //Means that 1 bit -> 2^8 integer
  unsigned long long xPowOfBase = 1;
  unsigned int i = 0;
  for(i = 1; i <= k; ++i)
      xPowOfBase *= base;//Means that token(x) has xPowOfBase x bit <-> x*2^8 integer
  int target_index=0;
  for(vector < string >::iterator sit=chrome.begin(); sit!=chrome.end(); sit++)
  {
      hash_count((*sit), target_index, xPowOfBase);
      target_index++;
  }
  //heapsort();
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
void heapsort(void)
{
  priority_queue <ppType, vector<ppType>, cmp >pq;
  //pq.capacity(10);
  map<unsigned long long, ppType>::iterator it;
  for(it=hashTable.begin(); it!=hashTable.end(); ++it)
  {
      pq.push(it->second);
  }
  ppType _top=pq.top();
  cout << endl;
  cout << "pq.count:" << _top.first << endl;
  int target_index=_top.second.first;//String index
  int start_index=_top.second.second;//Start index
  cout << " >> target_index :" << target_index << endl;
  cout << " >> start_index :" << start_index << endl;
  cout << " >> token :" << chrome[target_index].substr(start_index, k) << endl;
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

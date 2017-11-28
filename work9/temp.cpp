#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//string str;
vector < string > str;
int k;
pair<int, int> maxCountAndFirstPosition;

void file_read(void);
void frequencyChrome(void);
void print_answer(void);

int main(void)
{
    file_read();
    frequencyChrome();
    print_answer();
    return 0;
}
void file_read(void)
{
    string s;
    ifstream ifs("k-mer.inp");
    ifs >> k;
    while(!ifs.fail())
    {
        ifs >> s;
        //str.append(s);
        str.push_back(s);
    }
}
void frequencyChrome(void)
{
    unsigned const int base = 256;
    unsigned long long xPowOfBase = 1;
    int i = 0;
    for(i = 1; i <= k; ++i)
        xPowOfBase *= base;

    //Init firstXLengthSubString
    std::map<unsigned long long, std::pair<int, int> > hashTable;
    unsigned long long firstXLengthSubString = 0;
    for(i = 0; i < k; ++i)
    {
        firstXLengthSubString *= base;
        firstXLengthSubString += str[0][i];
    }
    unsigned long long nextXLengthSubstring = firstXLengthSubString;

    for(vector <string>::iterator str_it=str.begin(); str_it!=std::string.end(); ++str_it)
    {
        for(;(unsigned)i <= (*str_it).size(); ++i)
        {
            //find something
            if(hashTable.find(nextXLengthSubstring) != hashTable.end())
                ++hashTable[nextXLengthSubstring].first;
            else //not found -> then new element add
                hashTable.insert(std::make_pair(nextXLengthSubstring, std::make_pair(1, i - k)));
            //checking i size (bigger than k at least)
            if((unsigned)i != (*str_it).size())
            {   //Creating new hash of next elements
                nextXLengthSubstring *= base;
                nextXLengthSubstring += (*str_it)[i];
                nextXLengthSubstring -= (*str_it)[i - k] * xPowOfBase;
            }
        }
    }
    std::map<unsigned long long, std::pair<int, int> >::iterator it = hashTable.begin();
    std::map<unsigned long long, std::pair<int, int> >::iterator end_it = hashTable.end();
    maxCountAndFirstPosition = std::make_pair(0, -1); //weight || index

    for(;it != end_it; ++it)
    {
        if(maxCountAndFirstPosition.first < it->second.first)
            maxCountAndFirstPosition = it->second;
    }
}
void print_answer(void)
{
    ofstream ofs("k-mer.out");
    ofs << maxCountAndFirstPosition.first << std::endl;
    /*
    for(vector < string >::iterator it=str.begin(); it!=str.end(); it++)
    {
        if((*it).size() >= (unsigned)k)
          //ofs << (*it).substr(maxCountAndFirstPosition.second, k) << std::endl;
    }
    */
    cout << "a : " << maxCountAndFirstPosition.second << endl;
    cout << "k : " << k << endl;
    ofs.close();
}

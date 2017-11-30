#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

string str;
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
        str.append(s);
    }
}
void frequencyChrome(void)
{
    unsigned const int base = 256;
    unsigned long long xPowOfBase = 1;
    int i = 0;
    for(i = 1; i <= k; ++i)
        xPowOfBase *= base;

    unsigned long long firstXLengthSubString = 0;
    for(i = 0; i < k; ++i)
    {
        firstXLengthSubString *= base;
        firstXLengthSubString += str[i];
    }

    unsigned long long nextXLengthSubstring = firstXLengthSubString;

    std::map<unsigned long long, std::pair<int, int> > hashTable;
    for(;(unsigned)i <= str.size(); ++i)
    {
        if(hashTable.find(nextXLengthSubstring) != hashTable.end())
            ++hashTable[nextXLengthSubstring].first;
        else
            hashTable.insert(std::make_pair(nextXLengthSubstring, std::make_pair(1, i - k)));

        if((unsigned)i != str.size())
        {
            nextXLengthSubstring *= base;
            nextXLengthSubstring += str[i];
            nextXLengthSubstring -= str[i - k] * xPowOfBase;
        }
    }

    std::map<unsigned long long, std::pair<int, int> >::iterator it = hashTable.begin();
    std::map<unsigned long long, std::pair<int, int> >::iterator end_it = hashTable.end();
    maxCountAndFirstPosition = std::make_pair(0, -1);

    for(;it != end_it; ++it)
    {
        if(maxCountAndFirstPosition.first < it->second.first)
            maxCountAndFirstPosition = it->second;
    }
}
void print_answer(void)
{
    ofstream ofs("k-mer.out");
    //ofs << maxCountAndFirstPosition.first << std::endl;
    ofs << str.substr(maxCountAndFirstPosition.second, k) << std::endl;
    ofs.close();
}

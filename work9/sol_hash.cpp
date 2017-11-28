#include <iostream>
#include <string>
#include <map>
#include <algorithm>


int main()
{
    std::string s;
    int x;
    std::cin >> s >> x;

    unsigned const int base = 256; //Means that 1 bit -> 2^8 integer
    unsigned long long xPowOfBase = 1;
    int i = 0;
    for(i = 1; i <= x; ++i)
        xPowOfBase *= base;//Means that token(x) has xPowOfBase x bit <-> x*2^8 integer

    //step1.hashing :
    //Init first substring(0 ~ k(delimeter))
    unsigned long long firstXLengthSubString = 0;
    for(i = 0; i < x; ++i)
    {
        firstXLenxgthSubString *= base;
        firstXLengthSubString += s[i];
    }

    unsigned long long nextXLengthSubstring = firstXLengthSubString;
    std::map<unsigned long long, std::pair<int, int> > hashTable;

    //step2.start i = k + 1 until total string s.
    for(;i <= s.size(); ++i)
    {
        //find nextSubstring then count up
        if(hashTable.find(nextXLengthSubstring) != hashTable.end())
            ++hashTable[nextXLengthSubstring].first;
        //Not found then nextSubstring and Init value
        else
            hashTable.insert(std::make_pair(nextXLengthSubstring, std::make_pair(1, i - x)));//[i-x] : means that find the start index

        //Index i < toal String s
        //Then change nextSubstring
        if(i != s.size())
        {
            nextXLengthSubstring *= base;
            nextXLengthSubstring += s[i];
            //Modify the start Index of substrings to be checked
            nextXLengthSubstring -= s[i - x] * xPowOfBase;
        }
    }

    std::map<unsigned long long, std::pair<int, int> >::iterator it = hashTable.begin();
    std::map<unsigned long long, std::pair<int, int> >::iterator end_it = hashTable.end();
    std::pair<int, int> maxCountAndFirstPosition = std::make_pair(0, -1);

    for(;it != end_it; ++it)
    {
        if(maxCountAndFirstPosition.first < it->second.first)
            maxCountAndFirstPosition = it->second;
    }

    std::cout << maxCountAndFirstPosition.first << std::endl;
    std::cout << s.substr(maxCountAndFirstPosition.second, x) << std::endl;
    return 0;
}

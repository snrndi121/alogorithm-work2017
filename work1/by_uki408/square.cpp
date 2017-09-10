#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#define POW_NUM 2
#define MAX_NUM 1000000
#define MIN_NUM 1
#define MAX_RANGE 1000
#define MIN_RANGE 5
using namespace std;

int main()
{
    unsigned int sz=0;
    uint _data;
    vector < uint > data_seq;
    vector < uint > result;

    ifstream insq("square.inp");
    /* FILE CHECKING */
    if(insq.fail())
    {
        ;//return -1;
    } else
    {
        /* INPUT DATA READ OPEN*/
        insq >> sz;
        if(sz>=MIN_RANGE && sz<=MAX_RANGE)
        {
            result.reserve(sz);
            data_seq.reserve(sz);
            while(insq >> _data)
            {
        		/* DATA RANGE CHECKING */
                if(_data < MIN_NUM || _data > MAX_NUM)
                {
                    break;
                    //return -1;
                }
                else
                data_seq.push_back(_data);
            }
            /* INPUT DATA READ CLOSE*/
            insq.close();

            /* DATA SORTING */
            sort(data_seq.begin(), data_seq.end());

            /* ALGORITHM START */
            if(data_seq.size()==sz)
            {
                for(vector<uint>::iterator pin_a=data_seq.end()-1; pin_a!=data_seq.begin()+1; pin_a--)
                {
                    for(vector<uint>::iterator pin_b = (pin_a-1); pin_b!=data_seq.begin(); pin_b--)
                    {
                        double val = (*pin_a) - pow((double)*pin_b, POW_NUM);
        				        bool ch1=(val/1.0 == (int)val);
                        if(val>0 && ch1)
                        {
                            double target = sqrt(val);
                            bool ch2=(target/1.0 ==(int)target);
                            // BINARY SEARCH
                            if(ch2 && binary_search(data_seq.begin(), pin_b, target))
                            {
                                result.push_back(*pin_a);
                            } else{;}
                        } else{;}

                    }
                }
            } else{;}
            /* RESULT UNIQUE : ELIMINATE DUPLICATION */
            sort(result.begin(), result.end());
            vector<uint>::iterator dup;
            dup = unique(result.begin(), result.end());
            result.erase(dup, result.end());
        }
    }
    /* RESULT PRINT */
    // FILE;
    ofstream of("square.out");
    if(result.size())
    {
        for(vector <uint>::iterator it=result.begin(); it!=result.end(); ++it)
        {
            if(it != result.end()-1)
            {
              of << *it << ' ';
            } else
            {
              of << *it;
            }
        }
    } else
    {
        of << 0;
    }
    of.close();
    return 0;
}

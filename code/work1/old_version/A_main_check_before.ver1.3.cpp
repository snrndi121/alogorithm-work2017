#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <time.h>
#define POW_NUM 2
using namespace std;

/*
    * 'A' way : check if the result is generated. (First check)
		* A_ver1.3 : pow + pow -> sqrt(pow)
*/
int main()
{
	time_t st=0, end=0;
	st=clock();

    unsigned int sz=0;
	int _data;
    vector < int > data_seq;
	ifstream insq("square.inp");
    /* FILE CHECKING */
    if(insq.fail())
    {
        cout << ">> Cannot read the file !!! Checkout File" << endl;
        return -1;
    }
    /* INPUT DATA READ */
    insq >> sz;
    while(insq >> _data)
    {
        data_seq.push_back(_data);
    }
	insq.close();
    /* INPUT DATA CHECKING */
    if(sz != data_seq.size())
    {
		cout << "CONST SIZE :" << sz << ", ACTUAL SIZE :" << data_seq.size() << endl;
        cout << ">> File has wrong data parameters!!!Checkout File" << endl;
        return -4;
    } else
	{
		cout << " >> Reading is completed !!!\n";
	}
    /* DATA SORTING */
    sort(data_seq.begin(), data_seq.end());
    /* DATA PRINT */
    /*
    {
        cout << "------------------- data_ here ---------------------" << endl;
        for(vector<int>::iterator it=data_seq.begin(); it!=data_seq.end();++it)
        {
            cout << *it << ' ';
        }
        cout << "\n----------------------------------------------------\n\n";
    }
    */
    /* ALGORITHM START */
    vector < double > result;
	int count =0;
    /* cout << "\n>> algorithm is starting " << endl; */
	for(vector<int>::iterator pin_a=data_seq.begin(); pin_a!=data_seq.end()-2; pin_a++)
  {
        /* cout << "pin_a :" << (*pin_a) << endl; */
			for(vector<int>::iterator pin_b = (pin_a+1); pin_b!=data_seq.end()-1; pin_b++)
			{
	            double res_temp=(pow((double)*pin_a, POW_NUM) + pow((double)*pin_b, POW_NUM));
	            /* cout << "pin_b :" << (*pin_b) << endl; */
	            /* bsearch(address of key, addr of array, length of array, size of array, void*) */
							if(binary_search(data_seq.begin(), data_seq.end(), res_temp))
							{
								result.push_back(res_temp);
							} else
							{;
							}

			}
	}
    /* cout << ">> algorithm is done. Check out below the result \n\n";*/
    /* RESULT PRINT */

    if(result.size())
    {
        // cout << "result is here " << endl;
        for(vector <double>::iterator it=result.begin(); it!=result.end(); ++it)
        {
            cout << *it << ' ';
        }
        cout << "\n\n>> Done\n";
    } else
    {
		cout << ">> count :" << count << endl;
        cout << ">> result :" << result.size() << endl;
        cout << ">> There is no result or algorithm doesn't working. Try again " << endl;
    }

	end=clock();
	cout << "gap :" << (float)(end - st)/CLOCKS_PER_SEC << endl;
    return 0;
}

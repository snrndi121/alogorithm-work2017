#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <time.h>
#define POW_NUM 2
using namespace std;

/*
    * Issue : Which one is the more cost between pow and sqrt?
    * Issue
        * 'A' way : check if the result is generated. (First check)
        * 'B' way : check if the result are fully generated. It means that check is the last step.(Last check)
*/

int main()
{
	float gap=0;
	time_t startTime=0, endTime=0;
	startTime=clock();
    unsigned int sz=0;
	int _data;
    vector < int > data_seq;
    ifstream insq("square_in.txt");
    /* ifstream insq("square_in_2.txt"); */
    /* FILE CHECKING */
    if(insq.fail())
    {
        cout << ">> Cannot read the file !!! Checkout File" << endl;
        return -1;
    }
    /* DATA READ */
    insq >> sz;
    while(insq >> _data)
    {
        data_seq.push_back(_data);
    }
    /* DATA CHECKING */
    if(sz != data_seq.size())
    {
        cout << ">> File has wrong data parameters!!!Checkout File" << endl;
        return -4;
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
    //vector < int > all_temp;
    vector < int > temp_all;
    {
        /* cout << "\n>> algorithm is starting " << endl; */
        for(vector<int>::iterator pin_a=data_seq.begin(); pin_a!=data_seq.end(); pin_a++)
        {
            /* cout << "pin_a :" << (*pin_a) << endl; */
            for(vector<int>::iterator pin_b = (pin_a+1); pin_b!=data_seq.end(); pin_b++)
            {
                /* cout << "pin_b :" << (*pin_b) << endl; */
                /* 제곱 계산 */
                for(vector<int>::iterator pin_res =(pin_b+1); pin_res!=data_seq.end(); pin_res++)
                {
                    double res_temp=pow((double)*pin_a, POW_NUM) + pow((double)*pin_b, POW_NUM);
                    /* 제곱기 비교 */
                    /* cout << "res_temp : " << res_temp << " compare " << (*pin_res) << endl; */
                    temp_all.push_back(res_temp);
                    /*
                    if(res_temp == (*pin_res))
                    {
                        result.push_back(res_temp);
                    }
                    */
                }

            }
            /* cout << endl; */
        }
        /* cout << ">> algorithm is done. Check out below the result \n\n";*/
    }
    /* CHECK */
    /* 기존결과에 unique 적용 */
    vector <int>::iterator pos;
    pos=unique(temp_all.begin(), temp_all.end());
    temp_all.erase(pos, temp_all.end());

    /* COMPARE */
    vector <int> result;
    cout << "test " << endl;
    for(vector<int>::iterator it1=data_seq.begin(); it1!=data_seq.end(); it1++)
    {
        for(vector<int>::iterator it2=temp_all.begin(); it2!=temp_all.end(); it2++)
        {
            if(*it1 == *it2)
                result.push_back(*it1);
        }
    }
    /* RESULT PRINT */

    if(result.size())
    {
        /* cout << "result is here " << endl; */
        for(vector <int>::iterator it=result.begin(); it!=result.end(); ++it)
        {
            cout << *it << ' ';
        }
        cout << "\n\n>> Done\n";
    } else
    {

        cout << ">> result :" << result.size() << endl;
        cout << ">> There is no result or algorithm doesn't working. Try again " << endl;
    }
	endTime=clock();
	gap=(float)(endTime - startTime)/(CLOCKS_PER_SEC);
	cout << "gap :" << gap << endl;
    return 0;
}

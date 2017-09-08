#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <time.h>
#define POW_NUM 2
#define MIN_NUM 1
#define MAX_NUM 1000000
using namespace std;

/*
    * 'A' way : check if the result is generated. (First check)
		* A_ver1.4 updated
        * bineary_search(data.begin(), data.end(), target) -> binary_search((pin_b + 1), data.end(), target)
        * pow + pow -> sqrt(pow)
*/
/*
void compareFile(void) 
{
	ifstream a("3.out");
	ifstream b("square.out");
	
	int _da, _db;
	int count =0;
	while(a >> _da && b >> _db)
	{
		if(_da != _db)
		{
			cout << "\ncount :" << count++ << endl;
			cout << "not sam!!!" << endl;
			cout << "a :" << _da <<", b:" << _db << endl;
			return ;
		}
	}	
	cout << ">> compare is right !!! " << endl;	
}
*/
int main()
{
	/* TIME CHECKING START *//* 
	time_t st=0, end=0; 
	st=clock();
	*/
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

    /* INPUT DATA READ OPEN*/
    insq >> sz;
    data_seq.reserve(sz);
    while(insq >> _data)
    {
        if(_data < MIN_NUM || _data > MAX_NUM)
        {
            cout << "wrong data !!!" << endl;
            return -1;
        }
        data_seq.push_back(_data);
    }
    /* INPUT DATA READ CLOSE*/
	insq.close();

    /* INPUT DATA CHECKING *//*
    if(sz != data_seq.size())
    {
		cout << "CONST SIZE :" << sz << ", ACTUAL SIZE :" << data_seq.size() << endl;
        cout << ">> File has wrong data parameters!!!Checkout File" << endl;
        return -4;
    } else
	{
		cout << " >> Reading is completed !!!\n";
	}
	*/
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
    vector < int > result;
	for(vector<int>::iterator pin_a=data_seq.end()-1; pin_a!=data_seq.begin()+1; pin_a--)
    {
			for(vector<int>::iterator pin_b = (pin_a-1); pin_b!=data_seq.begin(); pin_b--)
			{
			    double val = (*pin_a) - pow((float)*pin_b, POW_NUM);
				bool ch1=(val/1.0 == (int)val);
			    if(val>0 && ch1)
                {
                    double target = sqrt(val);
					bool ch2=(target/1.0 ==(int)target);
                    // binary_search(start, end, target)
                    if(ch2&&binary_search(data_seq.begin(), pin_b, target))
                    {
                        result.push_back(*pin_a);
                    } else{;}
                } else{;}

			}
	}
    /* RESULT UNIQUE : ELIMINATE DUPLICATION */
    vector<int>::iterator dup;
    dup = unique(result.begin(), result.end());
    result.erase(dup, result.end());

    // cout << ">> algorithm is done. Check out below the result \n\n";
    /* RESULT PRINT */
    // FILE
    ofstream of("square.out");
    if(result.size())
        for(vector <int>::iterator it=result.end()-1; it>=result.begin(); --it) {
            of << *it << ' ';
        }
    else
        of << 0;
    of.close();
    // CONSOLE 
	/*
    if(result.size())
    {
        // cout << "result is here " << endl;
        for(vector <int>::iterator it=result.end()-1; it>=result.begin(); --it)
        {
            cout << *it << ' ';
        }
        cout << "\n\n>> Done\n";
    } else
    {
        cout << ">> result :" << result.size() << endl;
        cout << ">> There is no result or algorithm doesn't working. Try again " << endl;
    }
	*/
	//compareFile();
	/* TIME CHECKING STOP *//*
	end=clock();
	cout << "gap :" << (float)(end - st)/CLOCKS_PER_SEC << endl;
	*/
    return 0;
}

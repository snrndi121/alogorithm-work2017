#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#define MAX_NUM 1000
using namespace std;


int main(void)
{
	vector <int> _data;
	char checkDup[MAX_NUM]={false,};
	
	ofstream of("square.inp");
	srand((unsigned)time(NULL));
	for(uint i=0; i<MAX_NUM;) 
	{
		int temp=rand() % MAX_NUM + 1;
		if(checkDup[temp] == false)
		{
			checkDup[temp]=true;
			_data.push_back(temp);
			++i;
		}
	}	
	if(MAX_NUM == _data.size())
	{
		cout << ">> good" << endl;
		of << _data.size() << '\n';
		for(uint i=0; i<MAX_NUM; ++i) {
			of << _data[i] << ' ';	
		}
	}
	else
		cout << ">> bad" << endl;
	of.close();
	return 0;
}


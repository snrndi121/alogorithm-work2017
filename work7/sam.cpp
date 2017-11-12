#include <vector>
#include <iostream>

using namespace std;

int main(void)
{
	vector < int > temp;

	for(int i=0; i<10; ++i)
	{
		temp.push_back(i);
	}
	
	for(vector < int >::iterator it=temp.begin();
		it!=temp.end(); ++it)
	{	
		cout << (*it) << ' ' << endl;
	}
	cout << endl;
	cout << "--- test ---- " << endl;
	
	for(vector < int >::iterator it=temp.begin();
		it!=temp.end(); ++it)
	{
		if((*it) == 5)
		{
			temp.erase(it);	
		}
	}	

	for(unsigned int i=0; i<temp.size(); ++i)
	{
		cout << temp[i] << ' ';
	}
	cout << endl;

	return 0;
}

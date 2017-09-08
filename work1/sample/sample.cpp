#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main(void) 
{
vector<int> a;

a.push_back(1);
a.push_back(1);
a.push_back(2);
a.push_back(1);
a.push_back(2);
a.push_back(1);
a.push_back(2);
a.push_back(1);
a.push_back(1);
a.push_back(2);
a.push_back(1);
a.push_back(2);

sort(a.begin(), a.end());

vector<int>::iterator it;
it=unique(a.begin(), a.end());
a.erase(it, a.end());
for(uint i=0; i<a.size(); ++i)
	cout << a[i] << endl;


return 0;
}

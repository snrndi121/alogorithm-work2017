#include <iostream>
#include <queue>
#include <time.h>
#include <algorithm>

using namespace std;

int main(void)
{
	priority_queue <int> p;
	
	srand((unsigned)time(NULL));

	for(int i=0; i<10; ++i)
	{
		p.push(rand() % 10000);
	}
	p.push(1);
	p.push(1);
	while(!p.empty())
	{
		cout << p.top() << ' ';
		p.pop();
	}
	return 0;
}

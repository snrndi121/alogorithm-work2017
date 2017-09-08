#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

int main(void) 
{
	time_t s1=0, e1=0;
	int a,b;
	s1=clock();
	a=pow(932141, 2) + pow(323142, 2);
	cout << "a:" << a << endl;
	e1=clock();
	cout << "time_a :" << (float)(e1-s1)/CLOCKS_PER_SEC;
	s1=clock();
	b=sqrt(932141-pow(323142,2));
	cout << "\nb:" << b << endl;
	e1=clock();
	cout << "time_b :" << (float)(e1-s1)/CLOCKS_PER_SEC;
	
	return 0;
}

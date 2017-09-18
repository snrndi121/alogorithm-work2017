#include <iostream>
#include <fstream>
#include <cmath>
#define MATRIX 3
#define M(a,b) (a+b)/2.0
#define POW(a,b) pow(abs(a-b), 2)

using namespace std;

double distance(double* p, double* q); //Get distance p and q
bool isInteger(double _target);	//Check if _target is integer
double setInteger(double _mX, bool _rounds);	//Check range of the X and Then Change X to integer
int find_connect(double _point[3][MATRIX], double *_res); //Main algorithm
void setPointM(double* _m, double* _a, double * _b);	//modify the m, the middle of a and b

int main(void)
{
	// DATA INPUT
	double point[3][MATRIX];
	int label=0, index=0;

	ifstream ifs("connect.inp");
	while(ifs >> point[label][index++])
	{
		if(index %3 == 0) {label++; index=0;}
	}
	ifs.close();

	// ALGORITHM START
	double res[MATRIX];
	int result=find_connect(point, res);

	// PRINT RESULT
	ofstream of("connect.out");
	of << result;
	of.close();

	return 0;
}
double distance(double* p, double* q)
{
	double d = 0;
	double result;

	// CALCULATE DISTANCE
	for (int i=0; i < MATRIX; ++i)
	{
		double temp = POW(p[i], q[i]);
		d += temp;
	}
	result = sqrt(d);
	return result;
}
bool isInteger(double _target) {return _target == _target/1.0;}
void setPointM(double* _m, double* _a, double * _b)
{
	double t=(_m[0]-_a[0])/(_b[0]-_a[0]);
	for(int i=1; i<MATRIX; ++i)
	{
		_m[i]=_b[i]*t + (1-t)*_a[i];
	}
}
double setInteger(double _mx, bool _rounds)
{
	// Integer Check
	if(isInteger(_mx)) {return _mx;}

	// ROUNDS
	double rounds_mx=0;
	if(rounds_mx == 0)
	{	//if a->m
		rounds_mx=floor(_mx);
	} else
	{	//b->m
		rounds_mx=ceil(_mx);
	}
	return rounds_mx;
}
int find_connect(double _point[3][MATRIX], double *_res)
{
	// CALCULATE THE MIDDLE
	double m_ab[3];

	for (int i = 0; i < MATRIX; ++i) {
		m_ab[i] = M(_point[0][i], _point[1][i]);
	}
	// DISTANCE (x, p)
	double d_ap = distance(_point[0], _point[2]);
	double d_bp = distance(_point[1], _point[2]);
	double new_dist= 0;
	double old_dist= d_ap < d_bp? d_ap : d_bp;
	// If there at least middle between point 'a' and 'b'
	while(abs(_point[0][0]-_point[1][0]) > 1)
	{
		// Shorten d_ap
		if (d_ap >= d_bp)
		{
			// REPOINT M
			m_ab[0]=setInteger(m_ab[0], 0);
			setPointM(m_ab, _point[0], _point[1]);
			for (int i=0; i<MATRIX; ++i)
			{
				_point[0][i] = m_ab[i];
				m_ab[i]=M(_point[0][i], _point[1][i]);
			}
			d_ap = distance(_point[0], _point[2]);
			new_dist=d_ap;
		}
		//Shoten d_bp
		else if (d_ap < d_bp)
		{
			m_ab[0]=setInteger(m_ab[0], 1);
			setPointM(m_ab, _point[0], _point[1]);
			for (int i=0; i<MATRIX; ++i)
			{
				_point[1][i] = m_ab[i];
				m_ab[i] = M(_point[0][i], _point[1][i]);
			}
			d_bp = distance(_point[1], _point[2]);
			new_dist=d_bp;
		}
		//MINIMUM DISTANCE
		if(old_dist > new_dist)
			old_dist=new_dist;
	}
	//<--- THIS POINT : GET THE SHORTEST DISTANCE DONE
	return ceil(new_dist);
}

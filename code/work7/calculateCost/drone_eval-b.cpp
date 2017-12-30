#include <bits/stdc++.h>
using namespace std;
#define MAX (101)

int N;
int M;
int w_sum;

int W[MAX];
int X[MAX];
int Y[MAX];
vector<int> vlist;

bool load_input( ifstream& is ) {
    is >> N;
    if( (N>=MAX) || (N<1) )  { cout << "Incorrect input size" << endl; return false; }

    int i, cnt=0;
    while( is >> i ){
        is >> W[i] >> X[i] >> Y[i];
        w_sum += W[i];
        cnt++;
    }
    return ( N==cnt );
}

bool load_output( ifstream& is ) {
    int tmp;
    is >> M;
    while( is >> tmp )
        vlist.push_back(tmp);
	cout << "M size :" << M << endl;
	cout << "vlist_size :" << vlist.size() << endl;
    return ( (unsigned)M==vlist.size() );
}

bool check_output() {

    vector<int> t(vlist.begin(), vlist.end());
    t.pop_back();
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());

    if( !( (N+1)==M ) )                     { cout << "Output Wrong : Incorrect visit size"             << endl; return false; }
    if( ! (t.size()==vlist.size())-1 )      { cout << "Output Wrong : Visit duplication"                << endl; return false; }
    if( (t[0]<1) || t[M-2]>N )              { cout << "Output Wrong : Visit out of Range"               << endl; return false; }
    if( (vlist[0]!=1) || (vlist[M-1]!=1) )  { cout << "Output Wrong : Depature & Destination must be 1" << endl; return false; }
    return true;
}

unsigned long long int calculate_energy() {

    int i, dist;
    unsigned long long int energy=0;
    int weight = w_sum+1;
    for( i=1; (unsigned)i<vlist.size(); ++i ){
        dist = abs(X[vlist[i]]-X[vlist[i-1]]) + abs(Y[vlist[i]]-Y[vlist[i-1]]);
        energy += weight*dist;
        weight -= W[vlist[i]];
    }
    return energy;
}

void err_file_ex( char* name ){ cout << "Error : The file [ " << name << " ] does not exist" << endl; }

int main(int argc, char *argv[]){

    char* inp_fname;
	char* outp_fname;

    /* 1. 파일명 입력 - 명령행 */
	if (argc < 3) {
		cout << "Error : No input file specifed" << endl;
		cout << "Usage : " << endl;
		cout << "> drone_eval.exe drone***.inp mydrone***.out" << endl;
		return 0;
	}
	inp_fname  = argv[1];
	outp_fname = argv[2];
	/* -------- End of 파일명-명령행-----------*/


	/* 2. 파일명 입력 - 소스코드 */
//	inp_fname = "drone.inp";
//	outp_fname = "drone.out";
	/* -------- End of 파일명-소스코드 -----------*/

	ifstream inp(inp_fname );
	ifstream out(outp_fname);
	if( !inp ) { err_file_ex(inp_fname ); return 1; }
    if( !out ) { err_file_ex(outp_fname); return 1; }
    cout << "Input file  : " << inp_fname  << endl;
    cout << "Output file : " << outp_fname << endl;

    if( !load_input(inp)  ) { cout << "Error : Invalid input file"  << endl; return 0; }
    if( !load_output(out) ) { cout << "Error : Invalid Output file" << endl; return 0; }
    if( !check_output()   ) { cout << "Program terminated"          << endl; return 0; }

    cout << "Energy : " << calculate_energy() << endl;

    return 0;
}

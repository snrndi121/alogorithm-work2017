#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

/* def */
typedef pair < int, int > pType;
// struct point save its point and index
typedef struct point
{
    point() { index=0, location=make_pair(0, 0);};
    point(unsigned _i, pType _p) { index=_i, location=make_pair(_p.first, _p.second);}
    unsigned index; //a index in which file was read
    pType location; //a point, "(x, y)"
    void operator = (const struct point& a) {index=a.index, location.first=a.location.first, location.second=a.location.second;}
}point;
//struct convex save its weight and point info
typedef struct convex
{
    convex() {weight=0;}
    convex(const point& _p) {weight=0, p=_p;}
    int weight; //means whether this point is convexhull. High weight means that it might be convexhull
    point p;  //a point, "(x, y)"
    bool operator < (const convex& a) const { return this->weight < a.weight;}
}convex;
typedef priority_queue < convex > prique_convex;

/* variable */
queue < point > input;//input data saving points and indexes
vector < int > output;//output data saving point's indexes

/* process */
//Read the input file, "spiral.inp"
void file_read();
//Find the next convexhull's index using current starting point
void find_convexHull();
//Write the output file, "spiral.out"
void file_write();

/* method */
//Calculate point's weight about a sample group
int setWeight(const pType& p);
//Calculate signed area from tree point, (p, q, r)
int signed_area(const pType& p, const pType& q, const pType& r);
//Update a sample group
void configureSample(prique_convex wq);
//Check the order of tree points
bool orderOnline(const pType& p, const pType& q, const pType& r);
//Print data below type, "output"
void print_vector(const vector < int >& v);
//Print data below type, "weightque"
void print_weight(prique_convex p);

int main()
{
    file_read();
    find_convexHull();
    file_write();
    return 0;
}

/* main::proc */
void file_read()
{
    int i=0, n=0 ,x=0, y=0;
    ifstream ifs("spiral.inp");
    if(ifs.fail())
    {
        cout << ">> no read file !!! " << endl;
        return ;
    }
    ifs >> n;
    while(i < n)
    {
        ifs >> x >> y;
        point _input((unsigned)++i, make_pair(x, y));
        input.push(_input);
    }
    ifs.close();
}
void find_convexHull()
{
    //part1. initialize
    pType init_p=make_pair(0, 0); // the initial starting point is (0, 0)
    int i=setWeight(init_p); //i : convexhull's index

    //part2. set the convexhull point
    while(!input.empty())
    {
        point ctop=input.front(); //get a top from the input
        input.pop(); //remove the top from the input  /* cout << "(" << i << "): (" << ctop.location.first << " ," << ctop.location.second << ")" << endl; */
        output.push_back(i); //Add its index into output
        i=setWeight(ctop.location); //find a next convexhull's index
    }/* print_vector(output); */
}
void file_write()
{
    ofstream ofs("spiral.out");
    for(vector < int >::iterator it=output.begin(); it != output.end(); ++it)
    {
        ofs << (*it) << ' ';
    }
    ofs.close();
}
/* optional::method */
int setWeight(const pType& p)
{
    //part1. Declare priority_queue - "max heap"
    prique_convex weightque;
    unsigned isize=input.size();/* cout << "\n1. current check : ";cout << "p :" << p.first << ", " << p.second; */

    //part2. Set the max heap by points' weight
    while(isize-- > 0)
    {
        point q=input.front();input.pop(); //point 'q'
        convex c(q); //the convex about the point 'q'
        /* cout << ", q:" << q.location.first << ", " << q.location.second << endl; cout << " 2.sample group size :" << input.size() << endl; */
        for(unsigned child=0; child < input.size(); ++child)
        {
              point r=input.front();input.pop(); /* cout << "r :" << r.location.first << ", " << r.location.second << endl; */
              int sign=signed_area(p, q.location, r.location);
              if(sign > 0) { ++c.weight; }  // the order is counterclockwise
              else if(sign < 0) { --c.weight; } //the order is clockwise
              else {  //the tree points are on one line
                  if(!orderOnline(p, q.location, r.location)) { --c.weight;} //the order is clockwise so the 'q' point has a penalty
                  else {;} //no penalty
              }
              input.push(r);
        }
        //the weight is set about the point 'q' then push into 'weightque'
        weightque.push(c);
        input.push(q);
        //Found convex
        /* if(c.weight + 1 == (int)input.size()) { cout << " >> convex !! " << endl;} */
    }
    //part3. Reconfigure the sample group using weightque
    configureSample(weightque);

    //part3. Extract the new convexhull from the weightque
    if(!weightque.empty())
    {
        convex wtop=weightque.top(); //this top means the convexhull
        /* print_weight(weightque); */
        return wtop.p.index;
    }
    else return -1;
}
void configureSample(prique_convex wq)
{
    queue < point > newinput;
    while(!wq.empty())
    {
        convex c=wq.top();
        newinput.push(c.p);
        wq.pop();
    }
    input.swap(newinput); //'input' is changed into 'newinput'
}
bool orderOnline(const pType& p, const pType& q, const pType& r)
{
      //If checking whether its the order is like 'p -> q -> r'
      //if p(x) == q(x) == r(x), then
      if(p.first == q.first && q.first == r.first)
      {
          bool upYbool=p.second < q.second && q.second < r.second;
          bool downYbool=r.second < q.second && q.second < p.second;
          return upYbool || downYbool;
      }
      //else
      bool rightXbool=p.first < q.first && q.first < r.first;
      bool leftXbool=r.first < q.first && q.first < p.first;
      return rightXbool || leftXbool;
}
int signed_area(const pType& p, const pType& q, const pType& r)
{
    /*  < signed_area >
        plus_val - minus_val > 0 ? : p->q->r is counterclockwise
        plus_val - minus_val < 0 ? : p->q->r is clockwise
    */
    int plus_val = p.first * q.second + q.first * + r.second + r.first * p.second;
    int minus_val = q.first * p.second + r.first * q.second + p.first * r.second;
    return plus_val - minus_val;
}
void print_vector(const vector < int >& v)
{   //cout << " --- print vector --- " << endl;
    for(vector < int >::const_iterator it=v.begin(); it != v.end(); ++it)
    {
        cout << (*it) << ' ';
    }
    cout << endl;
}
void print_weight(priority_queue < convex > p)
{   //cout << " --- print weight --- " << endl;
    while(!p.empty())
    {
        convex ctop=p.top();
        int x=ctop.p.location.first, y=ctop.p.location.second;
        cout << "point : (" << x << ", " << y;
        cout << "), weight :" << ctop.weight << endl;
        p.pop();
    }
    cout << " --- done weight --- \n\n";
}

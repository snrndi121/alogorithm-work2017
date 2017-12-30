// 3-Way Quicksort
void Quicksort3way(vector < string >& a)
{
    int len=a.size()-1;
		qsort3way(a, 0, len, 0);
}
// helper method for 3 way quicksort
void swap(vector < string >& a, int i, int j)
{
		string temp = a[i];
		a[i] = a[j];
		a[j] = temp;
}
void qsort3way(vector < string >& a, int l, int h, int d)
{
		if (h <= l) return;

		int lt = l, gt = h;
		int v = a[l][d];
		int i = l + 1;

		// partition
    while(i <= gt)
    {
        int t = a[i][d];
        if(t < v) { swap(a, lt++, i++); }
        else if(t > v) { swap(a, i, gt--);}
        else { i++; }
    }
		// a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]
		qsort3way(a, l, lt - 1, d);
		if(v >= 0) { qsort3way(a, lt, gt, d + 1); }
		qsort3way(a, gt + 1, h, d);
}

# Header
- writer : uki408
- email : snrndi4521@gmail.com
- upload-date : 2017-12-28

# Aim
- we want to find the counterclockwise convex hull in 2-dimension

# Description
- There are given the points (xi, yi) on the 2-dimension. We should scan those points and have to find
the convexhull in a counterclockwise direction. Besides, we have to print the order indexes.

- When some points are on a same line, a point at a close distance from stating point must be output first.
- The key is to find the closest point around a specific line axis in a counterclockwise direction. Or you
can use the 'signed area'

# Condition
- The number of points(N) : 4 <= N <= 30
- The range of x and y : 1 <= x, y <= 1000

# Input file & Output file
- Input file(spiral.inp)
line 1: 5
line 2: 900, 900
line 3: 960, 920
line 4: 940, 980
line 5: 900, 940
line 6: 900, 920

- Output file(spiral.out)
line 1:  2 3 4 5 1

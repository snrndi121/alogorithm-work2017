# Header
- coder : uki408
- email : snrndi4521@gmail.com
- upload-date : 2017-12-29

# Aim
- we want to find the maximum of the biconnected graph

# Description
- There is a graph. All vertexes are connected with other vertexes. In this situation, we have to find
the biconnected graph. Maybe there are many biconnected graph but we want to get its maximum.


# Condition
- The number of the vertexes(N) : 5 <= N <= 50
- Each vertex has a unique number

# Input file & Output file
- Input file(spiral.inp)
line 1: 15    //the number of vertexes, N
line 2: 1 10 12 0   //the vertex '1' is connected with 10 and 12. Besides, 0 means it is the end
line 3: 3 2 4 11 13 0
line 4: 8 10 12 7 15 0
line 5: ( ... )
line 6: 14 2 13 6 0

- Output file(spiral.out)
line 1:  2 3 4 5 6 13 14

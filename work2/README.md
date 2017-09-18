# coder : uki408
# email : snrndi4521@gmail.com
# upload-date : 2017-09-18

# Aim 
- we want to get the shotest length from the line to the point 'P'.

# condition
- there are the point A, B and P. Its dimention is 3. The line is started fron the A to the B. 

- The X axle range -1000 to 1000, and we only discuss X is a integer.

- S(t) = B*t + A*(1-t),

  this is a equation to get the point M on the line(A-B).

# Input file & Output file
- Input file has tree point infomation. They are in order, A,B,P.

  ex) 10 20 30
	  30 40 50
	  9  3  1
- Output file is the shortest length.But You have to round it up.

  ex) 27
	//the actual value is 26.1 but round it up. So the result is 27.

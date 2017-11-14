# coder : uki408
# email : snrndi4521@gmail.com
# upload-date : 2017-11-14

# Aim
- Achieve the way how to use backtracking algorithm
- Get the minimum cost

# Description
- There is a delivery company using drones. Customs' destinations are marked as 2-dimension point(x, y). Drones will be started from h(1) and deliverying burnens to h(i) point. Besides they should be back to h(1). The distance is measured as L(1)-metric, 'ManHattan-distance'.It means dist(h(i), h(j))= |x(i) - x(j)| + |y(i) - y(j)|.Furthermore drones have more energy as much as they have more burdens.
Therefore the cost can be gotten as (Weight * Distance).Having 'W' of burdens and flying 'L' distance, drones will consume (W+1) * L cost. The reason why 1 is plused is drones' own weight.

# Condition
- A drone have own weight, 1.
- You have to use only one drone.
- A drone sholud be come back h(1) point.

# Input file & Output file
- Input file
  6       //the number of delivery points
  1 0 1 5    //h(i) weight(i) x(i) y(i)
  2 1 4 3
  3 3 5 10
  6 2 13 4
  5 7 11 8
  4 6 8 8

- Output file is the minimum cost
  402

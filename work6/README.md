# coder : uki408
# email : snrndi4521@gmail.com
# upload-date : 2017-10-28

# Aim
- we want to get the best reward and the second best reward.

# Description
- There are k machines which inspect the material. It takes 1 day to do inspection.
 So We would receive the work requested from the client during 1 ~ T days. Notice that we should be strict on time so do not excess the due day(d(i)). If we are good, we will get the reward(c(i)). There are N tasks and K machines, What is the best reward and the second best reward?

ex) T=3, 6 tasks, 2 machine \n
 t(i) 1   2   3   4   5   6   7   8
 c(i) 32  25  14  10  5   98  3   21
 d(i) 2   3   3   2   1   1   2   3

-> (best)
   day   1   2   3
   m1    98  32  25
   m2    10  14  21

# Condition
- During the T days, We could use the K machines.
- If we finish a task, we get the reward(c(i)).
- The task has a info which means due and reward.

# Input file & Output file
- Input file

  ex)
  14 5 20 //the num of task || T days || K machins
   4 3  //task = reward || deadline
   2 5
  ..
  10 4
- Output file is the best reward and the second best reward.
  ex)
  452 450 //the best || the second best

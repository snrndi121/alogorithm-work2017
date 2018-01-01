# Header
- writer : uki408
- email : snrndi4521@gmail.com
- upload-date : 2017-12-03

# Aim
- we want to find the most frequent k-mer in the Gene problem.

# Description
- Every living things in universes have genes in order of chromosomes. It is composed of {a, g, t, c}. These can be represented as a long string. A 'k-mer' means a set of substrings in chromosomes 'S'. Therefore the k-mer is extracted by |S|-k+1 in the String 'S'. A specific pattern of substrings have so much of meanings that seaching k-mer is a important work. Thus, we will extract the Most frequent k-mer(MFK) from a chromosomes 'S'.

- In realities, we should find the MFK from some of animals like {mosquito, gorila, chimpanzee, human}. If the MFK is more than 1, we would choose the fatest in dictionary order. For example, The set of k-mer is {aaaa, abab, cccc}. 'aaaa' is the fastest in the dictionary. Therofore we can pick 'aaaa' easily. Besides, the lenth of a k-mer is given in the input file.

# Condition
- the k-mer has a lenth of N.
- If the k-mer has some of cases, we should choose the fatest in alpabetical order.
- We should read chromosomes given as one string.

# Input file & Output file
- Input file(k-mer.inp)
line 1:  5
line 2:  agtgtcttagtagag
line 3:  gtaac
line 4:  cccttatg
line 5:  cccttagtaga
line 6:  tgtaagctccagct
line 7:  gcgag

- Output file(k-mer.out)
line 1:  agctg

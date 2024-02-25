#usr/bin/bash

make re

echo ------------ sample test --------------
./PmergeMe 3 5 9 4
./PmergeMe 3 5 9 7 4
./PmergeMe 1 5 3 4 2 7 6 10 9 8
./PmergeMe 1 2 3 4 5 6 7 8 9 10

# ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
# For OSX USER:
./PmergeMe `jot -r 20 1 100000 | tr '\n' ' '`
./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`

echo ------------ error test --------------
./PmergeMe "-1" "2"

make fclean

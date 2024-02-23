#usr/bin/bash

make re

echo ------------ sample test --------------
./PmergeMe 3 5 9 7 4
./PmergeMe "-1" "2"
# ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
# For OSX USER:
# ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`

make fclean

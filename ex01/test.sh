#usr/bin/bash

make re
echo ------------ sample test --------------
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
./RPN "7 7 * 7 -"
./RPN "1 2 * 2 / 2 * 2 4 - +"
./RPN "(1 + 1)"
make fclean

#usr/bin/bash

make re

echo ------------ sample test --------------
./btc input.txt
echo ------------ error test --------------
./btc error.txt

make fclean

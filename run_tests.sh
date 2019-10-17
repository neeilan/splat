cmake -Dtest=ON
make
printf "\n\nTEST OUTPUT:\n\n"
./RunUnitTests
make clean

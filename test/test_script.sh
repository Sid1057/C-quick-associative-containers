#!bin/sh

./random_generator 1       | ./test
./random_generator 5       | ./test
./random_generator 10      | ./test
./random_generator 50      | ./test
./random_generator 100     | ./test
./random_generator 500     | ./test
./random_generator 1000    | ./test
./random_generator 5000    | ./test
./random_generator 10000   | ./test
./random_generator 50000   | ./test
./random_generator 100000  | ./test
# ./random_generator 500000  | ./test
# ./random_generator 1000000 | ./test

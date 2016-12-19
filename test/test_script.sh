#!bin/sh

g++ -O0 -std=c++11 -Wall -Wextra -o bin/quick_set_test quick_set_test.cpp
g++ -O0 -std=c++11 -Wall -Wextra -o bin/random_generator integer_generator.cpp

./bin/random_generator 1       | ./bin/quick_set_test 
./bin/random_generator 5       | ./bin/quick_set_test
./bin/random_generator 10      | ./bin/quick_set_test
./bin/random_generator 50      | ./bin/quick_set_test
./bin/random_generator 100     | ./bin/quick_set_test
./bin/random_generator 500     | ./bin/quick_set_test
./bin/random_generator 1000    | ./bin/quick_set_test
./bin/random_generator 5000    | ./bin/quick_set_test
./bin/random_generator 10000   | ./bin/quick_set_test
./bin/random_generator 50000   | ./bin/quick_set_test

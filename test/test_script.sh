#!bin/sh

./test/bin/random_generator 1       | ./test/bin/quick_set_test 
./test/bin/random_generator 5       | ./test/bin/quick_set_test
./test/bin/random_generator 10      | ./test/bin/quick_set_test
./test/bin/random_generator 50      | ./test/bin/quick_set_test
./test/bin/random_generator 100     | ./test/bin/quick_set_test
./test/bin/random_generator 500     | ./test/bin/quick_set_test
./test/bin/random_generator 1000    | ./test/bin/quick_set_test
./test/bin/random_generator 5000    | ./test/bin/quick_set_test
./test/bin/random_generator 10000   | ./test/bin/quick_set_test
./test/bin/random_generator 50000   | ./test/bin/quick_set_test

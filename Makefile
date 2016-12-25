CC=g++
APPFLAGS=-std=c++11 -O3 -Wall -Wextra
CFLAGS=-c -std=c++11 -Wall -Wextra

BINDIR=test/bin
OBJDIR=test/bin/obj

# all:

bloom_filter_test: $(OBJDIR)/bloom_filter_test.o
	$(CC) $^ -o $(BINDIR)/bloom_filter_test

$(OBJDIR)/bloom_filter_test.o: test/bloom_filter_test.cpp bloom_filter/bloom_filter.hpp
	$(CC) $(CFLAGS) test/bloom_filter_test.cpp -o $@

quick_set_test: $(OBJDIR)/quick_set_test.o $(OBJDIR)/integer_generator
	$(CC) $< -o $(BINDIR)/quick_set_test
	sh ./test/test_script.sh > test/results.txt

$(OBJDIR)/quick_set_test.o: test/quick_set_test.cpp
	$(CC) $(CFLAGS) test/quick_set_test.cpp -o $@

$(OBJDIR)/integer_generator: test/integer_generator.cpp
	$(CC) $(APPFLAGS) test/integer_generator.cpp -o $(BINDIR)/random_generator

clean:
	rm $(OBJDIR)/*.o
	rm $(BINDIR)/*.o

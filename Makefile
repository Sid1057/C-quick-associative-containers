CC=g++
CFLAGS=-c -std=c++11 -Wall -Wextra

BINDIR=test/bin
OBJDIR=test/bin/obj

# all:

bloom_filter_test: $(OBJDIR)/bloom_filter_test.o
	$(CC) $^ -o $(BINDIR)/bloom_filter_test

$(OBJDIR)/bloom_filter_test.o: test/bloom_filter_test.cpp bloom_filter/bloom_filter.hpp
	$(CC) $(CFLAGS) test/bloom_filter_test.cpp -o $@

quick_set_test: $(OBJDIR)/quick_set_test.o
	$(CC) $^ -o $(BINDIR)/quick_set_test

$(OBJDIR)/quick_set_test.o: test/quick_set_test.cpp
	$(CC) $(CFLAGS) test/bloom_filter_test.cpp -o $@

clean:
	rm $(OBJDIR)/*
	rm $(BINDIR)/*

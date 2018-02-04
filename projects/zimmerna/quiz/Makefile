CXX = gcc
CFLAGS = -Wall -fpic -coverage -lm -g

PROJ = testme
OBJS = testme.o

$(PROJ): $(OBJS)
	$(CXX) $(OBJS) -o $@

.c.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno *.so *.out
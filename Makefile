CXX=g++
RM=rm -f
CPPFLAGS=-std=c++11 -O3
LDFLAGS=-std=c++11 -O3

OBJS=sudoku.o grid.o solver.o strategies/eliminateConflicts.o strategies/guessOne.o strategies/resolveRequired.o

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

all: sudoku

sudoku: $(OBJS)
	$(CXX) $(LDFLAGS) -o sudoku $(OBJS)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) sudoku

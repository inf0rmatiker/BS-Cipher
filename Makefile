CPP=g++
CPPFLAGS=-Wall

default : main.o
	$(CPP) $(CPPFLAGS) -o cipher main.o

main.o : main.cc cipher.h
	$(CPP) $(CPPFLAGS) -c main.cc

clean :
	rm -rf *.o cipher *.hh

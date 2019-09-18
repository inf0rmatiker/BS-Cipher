CPP=g++
CPPFLAGS=-Wall

default : main.o Cipher.o
	$(CPP) $(CPPFLAGS) -o cipher main.o Cipher.o


Cipher.o:: Cipher.h 
main.o:: main.cc Cipher.o


clean :
	rm -rf *.o cipher *.h.gch

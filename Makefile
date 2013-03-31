all:main.o  
	g++ -g main.o  -o bmp
main.o:main.cpp pseudo.cpp
	g++ -std=c++0x -g -c main.cpp   -I . -o main.o
clean:
	rm -f *.o out.dat *~ 

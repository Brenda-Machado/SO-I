
main: cpu.o main.o main_class.o
	g++ main.o cpu.o main_class.o -o main

main.o: main.cc
	g++ -c main.cc

cpu.o: cpu.cc cpu.h traits.h
	g++ -c cpu.cc

main_class.o: main_class.cc main_class.h traits.h
	g++ -c main_class.cc
	
clean:
	rm *.o main


 

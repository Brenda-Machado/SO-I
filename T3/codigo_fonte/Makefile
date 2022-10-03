
main: cpu.o main.o main_class.o debug.o thread.o system.o
	g++ main.o cpu.o main_class.o debug.o thread.o system.o -o main

main.o: main.cc
	g++ -c main.cc

cpu.o: cpu.cc cpu.h traits.h
	g++ -c cpu.cc

main_class.o: main_class.cc main_class.h traits.h
	g++ -c main_class.cc

debug.o: debug.cc debug.h
	g++ -c debug.cc

thread.o: thread.cc thread.h
	g++ -c thread.cc

system.o: system.cc system.h
	g++ -c system.cc
	
clean:
	rm *.o main


 

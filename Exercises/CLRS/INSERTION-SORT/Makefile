objects = Main.o

INSERTION-SORT.exe: $(objects)
	g++ -O3 -static -o "INSERTION-SORT.exe" $(objects) 

Main.o: INSERTION-SORT.cpp 
	g++ -c -O3 "INSERTION-SORT.cpp" -o Main.o 

.PHONY : clean
clean :
	-del "INSERTION-SORT.exe" $(objects)

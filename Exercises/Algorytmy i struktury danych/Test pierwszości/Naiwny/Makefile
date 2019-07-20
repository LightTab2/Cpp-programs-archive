objects = Main.o

PrimeTest.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "PrimeTest.exe" $(objects) 

Main.o: PrimeTest.cpp 
	g++ -c -O3 "PrimeTest.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "PrimeTest.exe" $(objects)

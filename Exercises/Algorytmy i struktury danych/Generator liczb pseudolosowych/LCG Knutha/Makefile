objects = Main.o

Random.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Random.exe" $(objects) 

Main.o: Random.cpp 
	g++ -c -O3 "Random.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Random.exe" $(objects)

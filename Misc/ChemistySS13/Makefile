objects = Main.o

Chemistry.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Chemistry.exe" $(objects) 

Main.o: Chemistry.cpp 
	g++ -c -O3 "Chemistry.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Chemistry.exe" $(objects)

objects = Main.o

Parzystosc.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Parzystosc.exe" $(objects) 

Main.o: Parzystosc.cpp 
	g++ -c -O3 "Parzystosc.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Parzystosc.exe" $(objects)

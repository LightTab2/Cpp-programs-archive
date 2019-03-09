objects = Main.o

Sprawdzarka Testow.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Sprawdzarka Testow.exe" $(objects) 

Main.o: Sprawdzarka\ Testow.cpp 
	g++ -c -O3 "Sprawdzarka Testow.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Sprawdzarka Testow.exe" $(objects)

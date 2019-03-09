objects = Main.o

Generator Testow.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Generator Testow.exe" $(objects) 

Main.o: Generator\ Testow.cpp 
	g++ -c -O3 "Generator Testow.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Generator Testow.exe" $(objects)

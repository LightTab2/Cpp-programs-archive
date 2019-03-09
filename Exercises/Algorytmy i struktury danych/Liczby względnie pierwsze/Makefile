objects = Main.o

Coprime.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Coprime.exe" $(objects) 

Main.o: Coprime.cpp 
	g++ -c -O3 "Coprime.cpp" -o Main.o

.PHONY: debug
debug:
	g++ -c "Coprime.cpp" -o Main.o
	g++ -o "Coprime.exe" $(objects) 

.PHONY : clean
clean :
	-del "Coprime.exe" $(objects)

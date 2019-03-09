objects = Main.o

Podzielnosc.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Podzielnosc.exe" $(objects) 

Main.o: Podzielnosc.cpp 
	g++ -c -O3 "Podzielnosc.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Podzielnosc.exe" $(objects)

objects = Main.o

Niepodzielnosc.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Niepodzielnosc.exe" $(objects) 

Main.o: Niepodzielnosc.cpp 
	g++ -c -O3 "Niepodzielnosc.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Niepodzielnosc.exe" $(objects)

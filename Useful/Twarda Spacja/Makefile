objects = Main.o

Twarda Spacja.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Twarda Spacja.exe" $(objects) 

Main.o: Twarda\ Spacja.cpp 
	g++ -c -O3 "Twarda Spacja.cpp" -w -o Main.o 

.PHONY: clean
clean :
	-del "Twarda Spacja.exe" $(objects)

objects = Main.o

Twarda Spacja HTML.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Twarda Spacja HTML.exe" $(objects) 

Main.o: Twarda\ Spacja\ HTML.cpp 
	g++ -c -O3 "Twarda Spacja HTML.cpp" -w -o Main.o 

.PHONY: clean
clean :
	-del "Twarda Spacja HTML.exe" $(objects)

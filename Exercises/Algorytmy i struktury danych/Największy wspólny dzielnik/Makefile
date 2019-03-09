objects = Main.o

NWD.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "NWD.exe" $(objects) 

Main.o: NWD.cpp 
	g++ -c -O3 "NWD.cpp" -o Main.o

.PHONY: debug
debug:
	g++ -c "NWD.cpp" -o Main.o
	g++ -o "NWD_db.exe" $(objects) 

.PHONY : clean
clean :
	-del "NWD.exe" $(objects)

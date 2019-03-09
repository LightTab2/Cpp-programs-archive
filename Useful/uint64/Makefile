objects = Main.o

128bitRSA.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "128bitRSA.exe" $(objects) 

Main.o: 128bitRSA.cpp 
	g++ -c -O3 "128bitRSA.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "128bitRSA.exe" $(objects)

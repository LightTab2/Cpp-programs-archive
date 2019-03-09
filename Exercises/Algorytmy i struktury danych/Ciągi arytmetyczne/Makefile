objects = Main.o

CiagiArytmetyczne.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "CiagiArytmetyczne.exe" $(objects) 

Main.o: CiagiArytmetyczne.cpp 
	g++ -c -O3 "CiagiArytmetyczne.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "CiagiArytmetyczne.exe" $(objects)

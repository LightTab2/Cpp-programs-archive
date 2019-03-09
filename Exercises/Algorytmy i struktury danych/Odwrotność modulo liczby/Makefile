objects = Main.o

Odmodulo.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Odmodulo.exe" $(objects) 

Main.o: Odmodulo.cpp 
	g++ -c -O3 "Odmodulo.cpp" -o Main.o

.PHONY: debug
debug:
	g++ -c "Odmodulo.cpp" -o Main.o
	g++ -o "Odmodulo.exe" $(objects) 

.PHONY : clean
clean :
	-del "Odmodulo.exe" $(objects)

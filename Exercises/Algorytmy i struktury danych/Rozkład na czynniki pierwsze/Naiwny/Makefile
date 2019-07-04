objects = Main.o

Factorization.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Factorization.exe" $(objects) 

Main.o: Factorization.cpp 
	g++ -c -O3 "Factorization.cpp" -o Main.o

.PHONY: debug
debug:
	g++ -c "Factorization.cpp" -o Main.o
	g++ -o "Factorization.exe" $(objects) 

.PHONY : clean
clean :
	-del "Factorization.exe" $(objects)

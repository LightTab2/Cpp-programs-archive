objects = Main.o

UselessMultiplyBy4.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "UselessMultiplyBy4.exe" $(objects) 

Main.o: UselessMultiplyBy4.cpp 
	g++ -c -O3 "UselessMultiplyBy4.cpp" -w -o Main.o 

.PHONY: clean
clean :
	-del "UselessMultiplyBy4.exe" $(objects)

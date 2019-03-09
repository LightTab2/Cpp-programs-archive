objects = Main.o

Generator liczb doskonalych drugiego rodzaju.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Generator liczb doskonalych drugiego rodzaju.exe" $(objects) 

Main.o: Generator\ liczb\ doskonalych\ drugiego\ rodzaju.cpp 
	g++ -c -O3 "Generator liczb doskonalych drugiego rodzaju.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Generator liczb doskonalych drugiego rodzaju.exe" $(objects)

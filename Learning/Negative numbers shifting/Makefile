objects = Main.o

Negative numbers shifting.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Negative numbers shifting.exe" $(objects) 

Main.o: Negative\ numbers\ shifting.cpp 
	g++ -c -O3 "Negative numbers shifting.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Negative numbers shifting.exe" $(objects)

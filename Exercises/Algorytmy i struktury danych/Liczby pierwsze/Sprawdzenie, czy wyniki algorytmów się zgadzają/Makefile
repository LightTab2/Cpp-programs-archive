objects = Main.o

Check.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Check.exe" $(objects) 

Main.o: Check.cpp 
	g++ -c -O3 "Check.cpp" -o Main.o

.PHONY: debug
debug:
	g++ -c "Check.cpp" -o Main.o
	g++ -o "Check.exe" $(objects) 

.PHONY : clean
clean :
	-del "Check.exe" $(objects)

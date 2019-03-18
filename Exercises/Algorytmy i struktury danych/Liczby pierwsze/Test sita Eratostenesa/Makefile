objects = Main.o

Prime.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Prime.exe" $(objects) 

Main.o: Prime.cpp 
	g++ -c -O3 "Prime.cpp" -o Main.o

.PHONY: debug
debug:
	g++ -c "Prime.cpp" -o Main.o
	g++ -o "Prime.exe" $(objects) 

.PHONY : clean
clean :
	-del "Prime.exe" $(objects)

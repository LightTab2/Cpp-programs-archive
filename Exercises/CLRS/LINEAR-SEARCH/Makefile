objects = Main.o

LINEAR-SEARCH.exe: $(objects)
	g++ -O3 -static -o "LINEAR-SEARCH.exe" $(objects) 

Main.o: LINEAR-SEARCH.cpp
	g++ -c -O3 "LINEAR-SEARCH.cpp" -o Main.o 

.PHONY : clean
clean :
	-del "LINEAR-SEARCH.exe" $(objects)

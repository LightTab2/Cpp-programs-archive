objects = Main.o

KazdyPodzielnosc.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "KazdyPodzielnosc.exe" $(objects) 

Main.o: KazdyPodzielnosc.cpp 
	g++ -c -O3 "KazdyPodzielnosc.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "KazdyPodzielnosc.exe" $(objects)

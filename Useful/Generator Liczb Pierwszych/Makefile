objects = Main.o

Generator liczb pierwszych.exe: $(objects)
	g++ -O3 -fwhole-program -D DNDEBUG -o "Generator liczb pierwszych.exe" $(objects) 

Main.o: Generator\ liczb\ pierwszych.cpp 
	g++ -c -O3 "Generator liczb pierwszych.cpp" -w -o Main.o

.PHONY : clean
clean :
	-del "Generator liczb pierwszych.exe" $(objects)
